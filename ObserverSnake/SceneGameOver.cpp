#include "SceneGameOver.h"
#include "Game.h"

// Constructor de khi tao mot SceneGameOver o Game.cpp
SceneGameOver::SceneGameOver(SceneStateMachine& sceneStateMachine)
	: Scene(), _sceneStateMachine(sceneStateMachine), gameOverMenu(nullptr) {}

// Cai nay de de~ dang nhan du lieu scene o Game.cpp
void SceneGameOver::SetSwitchToScene(std::unordered_map<std::string, unsigned int> stateInf)
{
	// Stores the id of the scene that we will transition to.
	_stateInf.merge(stateInf);
}

void SceneGameOver::SwitchTo(std::string mapName) // nay nhan vao mapName, la cai chuoi~ string dau tien
{
	auto it = _stateInf.find(mapName);

	if (it != _stateInf.end()) {
		_sceneStateMachine.SwitchTo(it->second);
	}
}

// Khi no duoc tao ra, ham nay chay cung voi constructor
void SceneGameOver::OnCreate()
{
	gameOverMenu = new Menu(
		{ L"Yes", L"Back to main menu" },
		std::bind(
			[this](unsigned int listitem) {
				switch (listitem) {
				case 0:
					// Play again, switch to scene choose map
					SwitchTo("SceneGame"); 

					break;
				case 1:
					// Back to main menu
					_sceneStateMachine.SwitchTo(0);
					break;
				}
			},
			std::placeholders::_1
		)
	);
}

// Con may cai nay phai co de handle action cua menu
void SceneGameOver::OnActivate() {
	
	gameOverMenu->OnActivate();
}

void SceneGameOver::OnDeactivate()
{
	// Clear map
	gameOverMenu->OnDeactivate();
}

void SceneGameOver::ProcessInput() {
	Console::TextColor(ColorCode_Cyan);
	Console::gotoXY(SCREEN_WIDTH / 2 - (9 / 2), SCREEN_HEIGHT / 4);

	auto marginLeft = SCREEN_WIDTH / 10 * 2 + 6;

	std::vector<std::string> gameOverText = {
		" .---.   .--.  .-.   .-..----.    .----. .-. .-..----..----. ",
		"/   __} / {} \\ |  `.'  || {_     /  {}  \\| | | || {_  | {}  }",
		"\\  {_ }/  /\\  \\| |\\ /| || {__    \\      /\\ \\_/ /| {__ | .-. \\",
		" `---' `-'  `-'`-' ` `-'`----'    `----'  `---' `----'`-' `-'"
	};

	int j = 11;
	for (auto i : gameOverText) {
		Console::gotoXY(marginLeft, j++);
		std::cout << i;
	}
	//std::wcout << L"GAME OVER" << std::endl;
	Console::gotoXY(SCREEN_WIDTH / 2 - (28 / 2), SCREEN_HEIGHT / 4 + 1);
	std::wcout << L"DO YOU WANT TO PLAY AGAIN ?" << std::endl;
	gameOverMenu->ProcessInput();
}

void SceneGameOver::OnDestroy()
{
	// Clear map
	gameOverMenu->OnDeactivate();

	delete gameOverMenu;
}
