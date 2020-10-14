#include "Snake.h"
#include "SceneGame.h"
#include "Wall.h"
#include "Gate.h"
#include "Gift.h"
#include "Rocket.h"
#include "ThroughWall.h"
#include "X2Point.h"
#include "Player.h"
#include "Game.h"
#include "SceneGame.h"

Snake::Snake(int x, int y, std::shared_ptr<SceneGame> board, int color, char character) : Object(x, y) {
	_direction = Direction::idle;
	_dead = false;
	_board = board;
	_speed = 1.0;
	_speedTime = 0;
	_throughWallTime = 0.0;
	_x2PointTime = 0.0;

	_color = color;
	_character = character;

	// Initialize with a segment (assume it is snake's head)
	auto segment = std::dynamic_pointer_cast<SnakeSegment>(_board->addObject(ObjectType::snake_segment, x, y));
	segment->setColor(_color);
	segment->setCharacter(_character);

	segments.push_back(segment);
}

void Snake::setSkin() {
	std::shared_ptr<Player> player;

	if (player = getPlayer()) {
		Skin skin = player->getSnakeSkin();

		setColor(skin.color);
		setCharacter((wchar_t) skin.character);
	}
}
// Reset on next round
void Snake::resetStatus() {
	_direction = Direction::idle;
	_throughWallTime = 0;
	_x2PointTime = 0;
	_speed = 1;
	_speedTime = 0;
	_dead = false;
}
void Snake::setDead() {
	_dead = true;
}

Direction Snake::getDirection() { return _direction; }
void Snake::setDirection(Direction direction) { _direction = direction; }

// Buff functions
double Snake::getSpeed() { return _speed; }
bool Snake::isThroughWall() {
	if (_throughWallTime > 0) {
		return true;
	}
	return false;
}
bool Snake::isX2Point() {
	if (_x2PointTime > 0) {
		return true;
	}
	return false;
}
void Snake::setSpeed(double speed, double speedTime)
{
	_speed = speed;
	_speedTime = speedTime;
}
void Snake::setX2Point(double time)
{
	_x2PointTime = time;
}
bool Snake::isdead() {
	return _dead;
}

// Timer callbacks
void Snake::ThroughWallDecrease() {
	if (_throughWallTime < 0) {
		_throughWallTime = 0;
	}
	else if (_throughWallTime > 0) {
		_throughWallTime -= double(SNAKE_MOVE_SPEED) / 1000 / _speed;
	}
}
void Snake::SpeedTimeDecrease() 
{
	if (_speedTime < 0) {
		_speed = 1.0;
		_speedTime = 0;
	}
	else if(_speedTime > 0) {
		_speedTime -= double(SNAKE_MOVE_SPEED) / 1000 / _speed;
	}
}
void Snake::X2PointDecrease()
{
	if (_x2PointTime < 0) {
		_x2PointTime = 0;
	}
	else if (_x2PointTime > 0) {
		_x2PointTime -= double(SNAKE_MOVE_SPEED) / 1000 / _speed;
	}
}

// Skill
void Snake::HandleSkillKey()
{
	//TODO: the same thing to snake 1
	for (int i = 0; i < 3; i++) {
		if (GetAsyncKeyState((int)_keys[i].key)) {
			if (!activeItem(i + 1)) {
				Console::TextColor(ColorCode_DarkCyan);
				Console::gotoXY(0, 0);
				std::cout << "                                                               ";
				Console::gotoXY(0, 0);
				std::cout << "You don't have any item on slot " << i + 1 << ".";
			}
		}
	}
}
void Snake::setSkillKey(std::vector<KeyDescription> keys)
{
	_keys = keys;
}
void Snake::drawSkillBox() {
	if (!_player) return;
	short marginLeft = getPlayer()->getSkillUIMarginLeft();

	Console::drawRect({ marginLeft, 10 }, { marginLeft + 4, 12 });
	Console::drawRect({ marginLeft, 13 }, { marginLeft + 4, 15 });
	Console::drawRect({ marginLeft, 16 }, { marginLeft + 4, 18 });

	
	Console::TextColor(ColorCode_Cyan);
	Console::gotoXY(marginLeft - 1, 8);
	std::cout << "Items";

	Console::TextColor(ColorCode_Pink);
	// Skill1
	Console::gotoXY(marginLeft - 1, 12);
	std::cout << _keys[0].keyName;

	Console::gotoXY(marginLeft, 11);
	std::cout << "Empty";

	// Skill2
	Console::gotoXY(marginLeft - 1, 15);
	std::cout << _keys[1].keyName;

	Console::gotoXY(marginLeft, 14);
	std::cout << "Empty";

	// Skill3
	Console::gotoXY(marginLeft - 1, 18);
	std::cout << _keys[2].keyName;

	Console::gotoXY(marginLeft, 17);
	std::cout << "Empty";
}

// Through wall functions
bool Snake::dieInNextStep(int &step, const int &score) 
{
	if (_direction == Direction::idle) return false;
	auto x = _x, y = _y;

	switch (_direction) {
	case Direction::up: {
		y -= step;
		break;
	}
	case Direction::down: {
		y += step;
		break;
	}
	case Direction::left: {
		x -= step;
		break;
	}
	case Direction::right: {
		x += step;
		break;
	}
	}
	
	// if _snake get over border
	if (x > _board->_position.X + _board->_width) {
		x = _board->_position.X;

		step -= _board->_width + 1;
	}
	else if (x < _board->_position.X) {
		x = _board->_position.X + _board->_width;

		step += _board->_width + 1;
	}
	else if (y > _board->_position.Y + _board->_height) {
		y = _board->_position.Y;

		step -= _board->_height + 1;
	}
	else if (y < _board->_position.Y) {
		y = _board->_position.Y + _board->_height;

		step -= _board->_height;
	}

	for (auto i : _board->objects) {
		if (std::dynamic_pointer_cast<Wall>(i) 
			|| std::dynamic_pointer_cast<SnakeSegment>(i) 
			|| gateCollision({(short)x, (short)y}, score) == GateCollisionType::border) {
			if (i->getX() == x && i->getY() == y) return true;
		}
	}
	return false;
}
void Snake::setThroughWall(int time) {
	_throughWallTime += time;
}

// Set head pos
void Snake::setPos(int x, int y) {
	segments.front()->setPos(x, y);
}

// Collision
GateCollisionType Snake::gateCollision(unsigned int score) {
	if (score < _board->_currentRound * 100) return GateCollisionType::none;
	for (auto i : _board->objects) {
		if (std::dynamic_pointer_cast<Gate>(i)) {
			if ((i->getX() <= _x && i->getX() + 2 >= _x) && i->getY() - 1 == _y) return GateCollisionType::border; // top
			if ((i->getX() <= _x && i->getX() + 2 >= _x) && i->getY() + 1 == _y) return GateCollisionType::border; // bottom
			if (i->getX() == _x && i->getY() == _y) return GateCollisionType::door;
		}
	}
	return GateCollisionType::none;
}

// Check if in any specify coord that snake can get gate collision
GateCollisionType Snake::gateCollision(Coord coord, unsigned int score) {
	auto [X, Y] = coord;

	if (score < _board->_currentRound * 100) return GateCollisionType::none;
	for (auto i : _board->objects) {
		if (std::dynamic_pointer_cast<Gate>(i)) {
			if ((i->getX() <= X && i->getX() + 2 >= X) && i->getY() - 1 == Y) return GateCollisionType::border; // top
			if ((i->getX() <= X && i->getX() + 2 >= X) && i->getY() + 1 == Y) return GateCollisionType::border; // bottom
			if (i->getX() == X && i->getY() == Y) return GateCollisionType::door;
		}
	}
	return GateCollisionType::none;
}

bool Snake::bodyCollision() {
	for (auto i : _board->objects)
	{
		if (std::dynamic_pointer_cast<SnakeSegment>(i) && i != segments[0] && _x == i->getX() && _y == i->getY()) {
			return true;
		}
	}
	return false;
}
std::shared_ptr<Fruit> Snake::fruitCollision() {
	for (auto i : _board->objects) {
		if (std::dynamic_pointer_cast<Fruit>(i)) {
			if (i->getX() == _x && i->getY() == _y) return std::dynamic_pointer_cast<Fruit>(i);
		}
	}
	return nullptr;
}
std::shared_ptr<Gift> Snake::giftCollision() {
	for (auto i : _board->objects) {
		if (std::dynamic_pointer_cast<Gift>(i)) {
			if (i->getX() == _x && i->getY() == _y) return std::dynamic_pointer_cast<Gift>(i);
		}
	}
	return nullptr;
}
std::shared_ptr<Wall> Snake::wallCollision() {
	for (auto i : _board->objects) {
		if (std::dynamic_pointer_cast<Wall>(i)) {
			if (i->getX() == _x && i->getY() == _y) return std::dynamic_pointer_cast<Wall>(i);
		}
	}
	return nullptr;
}

// Behavious
void Snake::eatFruit(std::shared_ptr<Fruit> destinateFruit) {
	PlaySound(L"sounds\\eatFood.wav", NULL, SND_ASYNC);

	// Remove fruit
	destinateFruit->setPos(-1, -1); // this avoid destructor to clear new snake segment block
	_board->deleteFruit(-1, -1); // remove fruit with pos -1, -1

	// The size is automatically add on the next move.
	auto object = std::dynamic_pointer_cast<SnakeSegment>(_board->addObject(ObjectType::snake_segment, -1, -1));
	segments.push_back(object);
}
bool Snake::getItem(std::shared_ptr<Gift> gift) {
	int i = 1;

	while (_items[i]) {
		// Can't find a free slot
		if (i >= (ITEM_MAXSLOT + 1)) {
			PlaySound(L"sounds\\out-of-item-slot-x1.wav", NULL, SND_ASYNC);
			return false;
		}
		i++;
	}

	// found a slot
	if (!_items[i]) {
		PlaySound(L"sounds\\item-collect-x1.wav", NULL, SND_ASYNC);

		int n = rand() % 3 + 1;
		std::string itemNames[4] = { {""}, "Rocket", "Through Wall", "X2 Points" };
		Coord UISlotTextPosition[4] = { {-1, -1},
			{getPlayer()->getSkillUIMarginLeft(), 11},
			{getPlayer()->getSkillUIMarginLeft(), 14},
			{getPlayer()->getSkillUIMarginLeft(), 17}
		};

		switch (n) {
		case 1:
			_items[i] = std::make_shared<Rocket>();
			break;
		case 2:
			_items[i] = std::make_shared<ThroughWall>();
			break;
		case 3:
			_items[i] = std::make_shared<X2Point>();
			break;
		}

		//Console::gotoXY(0, 0);
		//std::cout << "\t\t\t\t\t\t\t\t\t\t\t";
		//Console::TextColor(ColorCode_Pink);
		//Console::gotoXY(0, 0);
		//std::cout << "You got a " << itemNames[n] << " on slot " << i << ".";

		Console::gotoXY(UISlotTextPosition[i].X, UISlotTextPosition[i].Y);
		std::cout << itemNames[n];
	}

	return true;
}
void Snake::turnHead(Direction direction) {
	if (direction == Direction::down && _direction == Direction::up) {
		return;
	}
	if (direction == Direction::up && _direction == Direction::down) {
		return;
	}
	if (direction == Direction::left && _direction == Direction::right) {
		return;
	}
	if (direction == Direction::right && _direction == Direction::left) {
		return;
	}

	if (!(direction != Direction::down && direction != Direction::up && direction != Direction::left && direction != Direction::right))
	{
		_direction = direction;
		PlaySound(L"sounds\\snake-move.wav", NULL, SND_ASYNC);
	}
}
void Snake::move(int step) {
	if (_direction == Direction::idle) return;
	//new head
	int x = segments.front()->getX(), y = segments.front()->getY();

	switch (_direction) {
	case Direction::up: {
		y -= step;
		break;
	}
	case Direction::down: {
		y += step;
		break;
	}
	case Direction::left: {
		x -= step;
		break;
	}
	case Direction::right: {
		x += step;
		break;
	}
	}

	// if _snake get over border
	if (x > _board->_position.X + _board->_width) {
		x = _board->_position.X;
	}
	else if (x < _board->_position.X) {
		x = _board->_position.X + _board->_width;
	}
	else if (y > _board->_position.Y + _board->_height) {
		y = _board->_position.Y;
	}
	else if (y < _board->_position.Y) {
		y = _board->_position.Y + _board->_height;
	}

	// Add new head object
	auto head = std::dynamic_pointer_cast<SnakeSegment>(_board->addObject(ObjectType::snake_segment, x, y));

	head->setColor(isX2Point() ? rand() % 10 + 1 : _color);
	head->setCharacter(_character);

	segments.push_front(head);

	// Update new head position
	_x = x;
	_y = y;

	// Delete tail object / old head object if its size was 1
	x = segments.back()->getX(), y = segments.back()->getY();

	_board->deleteSnakeSegment(x, y);

	segments.pop_back();
}
bool Snake::activeItem(int slot) {
	if (!_items[slot]) return false;

	_items[slot]->operate(shared_from_this());
	_items[slot].reset();

	Coord UISlotTextPosition[4] = { {-1, -1},
		{getPlayer()->getSkillUIMarginLeft(), 11}, 
		{getPlayer()->getSkillUIMarginLeft(), 14}, 
		{getPlayer()->getSkillUIMarginLeft(), 17} 
	};
	Console::gotoXY(UISlotTextPosition[slot].X, UISlotTextPosition[slot].Y);
	std::cout << "Empty        ";

	return true;
}
void Snake::enlonger(int n)
{
	for (int i = 0; i < n; i++) {
		auto segment = std::dynamic_pointer_cast<SnakeSegment>(_board->addObject(ObjectType::snake_segment, -1, -1));
		segments.push_back(segment);
	}
}
void Snake::paint() {
	Console::TextColor(ColorCode_Green);

	if(segments.front()->getX() != 0 && segments.front()->getY() != 0)
		segments.front()->paint();
}