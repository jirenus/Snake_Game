#pragma once
#include <deque>
#include <vector>
#include "SnakeSegment.h"
#include "Gate.h"
#include "Item.h"
#include "Player.h"

class SceneGame;
class Fruit;
class Wall;
class SceneSaveGame;
class Gift;

struct KeyDescription {
	char keyName;
	Key key;
};

const int SNAKE_MOVE_SPEED = 125;
const int ITEM_MAXSLOT = 3;

enum class Direction {
	idle = NULL,
	up = 'w',
	down = 's',
	left = 'a',
	right = 'd'
};

class Snake : public Object, public std::enable_shared_from_this<Snake> {
	friend class SceneSaveGame;
private:
	bool _dead;

	Direction _direction;
	std::deque<std::shared_ptr<SnakeSegment>> segments;
	std::shared_ptr<SceneGame> _board;
	std::shared_ptr<Item> _items[ITEM_MAXSLOT + 1];
	
	// Affected by item
	double _speed;
	double _speedTime;
	double _throughWallTime; 
	double _x2PointTime;

	std::vector<KeyDescription> _keys;

	int _color;
	char _character;

	// Binding
	std::shared_ptr<Player> _player;

public:
	Snake(int x, int y, std::shared_ptr<SceneGame> board, int color = ColorCode_DarkGreen, char character = 'O');

	void setSkin();
	
	double getSpeed();
	void resetStatus();
	bool isThroughWall();
	bool isStandingStill() { return _direction == Direction::idle; }
	bool isX2Point();

	void setSpeed(double speed, double speedTime = 30.0);
	void setX2Point(double time);
	void setThroughWall(int time);

	// Callbacks
	void ThroughWallDecrease();
	void SpeedTimeDecrease();
	void X2PointDecrease();

	void HandleSkillKey();
	void setSkillKey(std::vector<KeyDescription> keys);

	void drawSkillBox();

	// Check die, p/s: step is mutate is case of snake goes over border
	bool dieInNextStep(int& step, const int& score);

	void setPos(int x, int y);
	void setDead();

	Direction getDirection();

	void setDirection(Direction direction);

	void setColor(int color) { _color = color; }
	void setCharacter(char character) { _character = character; }

	GateCollisionType gateCollision(unsigned int score);
	GateCollisionType gateCollision(Coord coord, unsigned int score);
	bool bodyCollision();
	
	std::shared_ptr<Fruit> fruitCollision();
	std::shared_ptr<Gift> giftCollision();
	std::shared_ptr<Wall> wallCollision();

	void eatFruit(std::shared_ptr<Fruit> destinateFruit);
	bool getItem(std::shared_ptr<Gift> gift);
	void turnHead(Direction direction);

	void move(int step = 1);

	bool activeItem(int slot);
	
	// Enlonger n segments
	void enlonger(int n);

	void paint();
	bool isdead();

	std::shared_ptr<Player> getPlayer() { return _player; };
	void bindPlayer(std::shared_ptr<Player> player) { _player = player; };
};

