#include "SceneStateMachine.h"
#include "Menu.h"
#include"SceneScoreBoard.h"
#include<fstream>
#include"Game.h"
SceneScoreBoard::SceneScoreBoard(SceneStateMachine& sceneStateMachine) : Scene(), _sceneStateMachine(sceneStateMachine), mainMenu(nullptr) {}

void SceneScoreBoard::SetSwitchToScene(std::unordered_map<std::string, unsigned int> stateInf)
{
	// Stores the id of the scene that we will transition to.
	_stateInf.merge(stateInf);
}

void SceneScoreBoard::SwitchTo(std::string mapName) // nay nhan vao mapName, la cai chuoi~ string dau tien
{
	auto it = _stateInf.find(mapName);

	if (it != _stateInf.end()) {
		_sceneStateMachine.SwitchTo(it->second);
	}
}

void SceneScoreBoard::OnCreate()
{

}

void SceneScoreBoard::OnActivate() {

	DrawBorder();

	std::ifstream writer("ScoreBoard.txt", std::ios::in);
	std::string line;

	int countline = 0;

	//title
	Console::TextColor(ColorCode_Pink);
	Console::gotoXY(startPositionName, countline + 4);
	std::cout << "Name";
	Console::TextColor(ColorCode_Red);
	Console::gotoXY(startPositionRound, countline + 4);
	std::cout << "Round";
	Console::TextColor(ColorCode_Green);
	Console::gotoXY(startPositionScore, countline + 4);
	std::cout << "Score";

	//detail
	while (getline(writer, line)) {
		//name
		std::string temp = line.substr(0, line.find(" "));
		Console::gotoXY(startPositionName, countline + 5);
		Console::TextColor(ColorCode_Pink);
		std::cout << temp;

		//round
		temp = line.substr(line.find(" ") + 1, line.rfind(" ") - line.find(" ") - 1);
		Console::gotoXY(startPositionRound, countline + 5);
		Console::TextColor(ColorCode_Red);
		std::cout << temp;

		//score
		temp = line.substr(line.rfind(" ") + 1, line.size() - line.rfind(" ") - 1);
		Console::gotoXY(startPositionScore, countline + 5);
		Console::TextColor(ColorCode_Green);
		std::cout << temp;

		countline++;
	}
	writer.close();

	Console::gotoXY(startPositionName - 3, 20);
	std::cout << "PRESS ANYKEY TO BACK TO MY MENU";

	if (_getch()) {
		SwitchTo("MainMenuScene");
	}
}

void SceneScoreBoard::OnDeactivate()
{
	// Clear map
	mainMenu->OnDeactivate();
}

void SceneScoreBoard::Update() {

}

void SceneScoreBoard::OnDestroy()
{
	// Clear map
	mainMenu->OnDeactivate();
}

void SceneScoreBoard::DrawBorder() {
	Console::TextColor(7);

	std::cout << "                                     __________________________________________________" << std::endl;
	std::cout << "                                    /                                                  \\" << std::endl;
	std::cout << "                                    |    _________________________________________     |			   " << std::endl;
	std::cout << "                                    |   |                                         |    |			   " << std::endl;
	std::cout << "                                    |   |                                         |    |			   " << std::endl;
	std::cout << "                                    |   |                                         |    |			   " << std::endl;
	std::cout << "                                    |   |                                         |    |			   " << std::endl;
	std::cout << "                                    |   |                                         |    |			   " << std::endl;
	std::cout << "                                    |   |                                         |    |			   " << std::endl;
	std::cout << "                                    |   |                                         |    |			   " << std::endl;
	std::cout << "                                    |   |                                         |    |			   " << std::endl;
	std::cout << "                                    |   |                                         |    |			   " << std::endl;
	std::cout << "                                    |   |                                         |    |			   " << std::endl;
	std::cout << "                                    |   |                                         |    |			   " << std::endl;
	std::cout << "                                    |   |                                         |    |			   " << std::endl;
	std::cout << "                                    |   |                                         |    |			   " << std::endl;
	std::cout << "                                    |   |                                         |    |			   " << std::endl;
	std::cout << "                                    |   |                                         |    |			   " << std::endl;
	std::cout << "                                    |   |                                         |    |			   " << std::endl;
	std::cout << "                                    |   |                                         |    |			   " << std::endl;
	std::cout << "                                    |   |                                         |    |			   " << std::endl;
	std::cout << "                                    |   |_________________________________________|    |			   " << std::endl;
	std::cout << "                                    |                                                  |			   " << std::endl;
	std::cout << "                                    \\_________________________________________________/			   " << std::endl;
	std::cout << "                                           \\___________________________________/				   " << std::endl;
	std::cout << "                                         ___________________________________________				   " << std::endl;
	std::cout << "                                      _-'    .-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-.  --- `-_			   " << std::endl;
	std::cout << "                                   _-'.-.-. .---.-.-.-.-.-.-.-.-.-.-.-.-.-.-.--.  .-.-.`-_		   " << std::endl;
	std::cout << "                                _-'.-.-.-. .---.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-`__`. .-.-.-.`-_	   " << std::endl;
	std::cout << "                             _-'.-.-.-.-. .-----.-.-.-.-.-.-.-.-.-.-.-.-.-.-.-----. .-.-.-.-.`-_	   " << std::endl;
	std::cout << "                          _-'.-.-.-.-.-. .---.-. .-------------------------. .-.---. .---.-.-.-.`-_ " << std::endl;
	std::cout << "                         :-------------------------------------------------------------------------:" << std::endl;
	std::cout << "                         `---._.-------------------------------------------------------------._.---'" << std::endl;
}
