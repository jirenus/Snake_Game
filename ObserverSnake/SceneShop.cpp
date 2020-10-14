#include "SceneStateMachine.h"
#include "Menu.h"
#include "Game.h"
#include <functional>
#include <sstream>
#include "SceneShop.h"
#include "Player.h"

SceneShop::SceneShop(SceneStateMachine& sceneStateMachine) : Scene(), _sceneStateMachine(sceneStateMachine), mainMenu(nullptr) {}

void SceneShop::SetSwitchToScene(std::unordered_map<std::string, unsigned int> stateInf)
{
	// Stores the id of the scene that we will transition to.
	_stateInf = stateInf;
}

void SceneShop::SwitchTo(std::string mapName)
{
	auto it = _stateInf.find(mapName);

	if (it != _stateInf.end()) {
		_sceneStateMachine.SwitchTo(it->second);
	}
}

void SceneShop::OnCreate()
{
	std::vector<Skin> skins = {
		{L'O', ColorCode_DarkGreen, 0},
		{L'$', ColorCode_Yellow, 100},
		{178, ColorCode_Cyan, 200},
		{L'#', ColorCode_Cyan, 300},
		{L'@', ColorCode_Cyan, 200},
		{L'~', ColorCode_Cyan, 200}
	};

	std::vector<std::wstring> list;
	for (auto skin : skins) {
		std::wstringstream writer;
		for (int i = 0; i < 8; i++) writer << skin.character;
		writer << " - Price: " << skin.price;

		list.push_back(writer.str());
	}

	mainMenu = new Menu(
		list,
		std::bind(
			[this](unsigned int listitem, std::vector<Skin> skins) {
				if (listitem == 6) { 
					SwitchTo("MainMenuScene");
					return;
				}
				if (_sceneStateMachine.getPlayer(0)->getTotalScore() < skins[listitem].price) {
					Console::gotoXY(SCREEN_WIDTH - 70, SCREEN_HEIGHT - 1);
					std::cout << "\t\t\t\t\t\t\t\t\t";
					Console::TextColor(ColorCode_Cyan);
					Console::gotoXY(SCREEN_WIDTH - 70, SCREEN_HEIGHT - 1);
					std::cout << "You don't have enough score to buy this skin (current score: " << _sceneStateMachine.getPlayer(0)->getTotalScore() << ").";
				}
				else {
					Console::gotoXY(SCREEN_WIDTH - 70, SCREEN_HEIGHT - 1);
					std::cout << "\t\t\t\t\t\t\t\t\t";
					Console::TextColor(ColorCode_Cyan);
					Console::gotoXY(SCREEN_WIDTH - 70, SCREEN_HEIGHT - 1);
					std::cout << "You have successfully bought this skin (available total score: " << _sceneStateMachine.getPlayer(0)->getTotalScore() << ").";
					_sceneStateMachine.getPlayer(0)->setSnakeSkin(skins[listitem]);

					_sceneStateMachine.getPlayer(0)->setTotalScore(_sceneStateMachine.getPlayer(0)->getTotalScore() - skins[listitem].price);
				}
				Sleep(2000);
				SwitchTo("MainMenuScene");

			},
			std::placeholders::_1, skins
		)
	);
}

void SceneShop::OnActivate() {
	mainMenu->OnActivate();
}

void SceneShop::OnDeactivate()
{
	// Clear map
	mainMenu->OnDeactivate();
}

void SceneShop::Update() {
	mainMenu->ProcessInput();
}

void SceneShop::OnDestroy()
{
	// Clear map
	mainMenu->OnDeactivate();
}
