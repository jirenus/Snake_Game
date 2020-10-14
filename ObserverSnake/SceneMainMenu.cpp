#include "SceneMainMenu.h"
#include "SceneStateMachine.h"
#include "Menu.h"
#include "ScenePause.h"
#include "SceneGameOver.h"
#include "SceneGame.h"
#include "SceneSaveGame.h"
#include "SceneShop.h"
#include "SceneScoreBoard.h"
#include "SceneLoadGame.h"
#include <functional>

SceneMainMenu::SceneMainMenu(SceneStateMachine& sceneStateMachine) : Scene(), _sceneStateMachine(sceneStateMachine), mainMenu(nullptr) {}

void SceneMainMenu::SetSwitchToScene(std::unordered_map<std::string, unsigned int> stateInf)
{
	// Stores the id of the scene that we will transition to.
	_stateInf = stateInf;
}

void SceneMainMenu::SwitchTo(std::string mapName)
{
	auto it = _stateInf.find(mapName);

	if (it != _stateInf.end()) {
		_sceneStateMachine.SwitchTo(it->second);
	}
}

void SceneMainMenu::OnCreate()
{
	mainMenu = new Menu(
		{ L"Single player", L"Two players", L"Load game", L"Shop",L"Score Board", L"Exit" },
		std::bind(
			[this](unsigned int listitem) {
				// Create scene
				std::vector<std::wstring> maps = { L"ClassicMap1.dat", L"ClassicMap2.dat", L"ModernMap1.dat", L"ModernMap2.dat" };
				std::shared_ptr<SceneGame> gameScene1 = std::make_shared<SceneGame>(1, maps, _sceneStateMachine);
				std::shared_ptr<SceneGame> gameScene2 = std::make_shared<SceneGame>(2, maps, _sceneStateMachine);
				std::shared_ptr<ScenePause> pauseScene = std::make_shared<ScenePause>(_sceneStateMachine);
				std::shared_ptr<SceneGameOver> gameOverScene = std::make_shared<SceneGameOver>(_sceneStateMachine);
				std::shared_ptr<SceneShop> ShopScene = std::make_shared<SceneShop>(_sceneStateMachine);
				std::shared_ptr<SceneLoadGame> loadGameScene = std::make_shared<SceneLoadGame>(_sceneStateMachine);
				std::shared_ptr<SceneScoreBoard> scoreBoardScene = std::make_shared<SceneScoreBoard>(_sceneStateMachine);

				unsigned int gameSceneID1 = _sceneStateMachine.Add(gameScene1);
				unsigned int gameSceneID2 = _sceneStateMachine.Add(gameScene2);

				unsigned int loadGameSceneID = _sceneStateMachine.Add(loadGameScene);
				unsigned int pauseSceneID = _sceneStateMachine.Add(pauseScene);
				unsigned int gameOverSceneID = _sceneStateMachine.Add(gameOverScene);
				unsigned int ShopSceneID = _sceneStateMachine.Add(ShopScene);
				unsigned int ScoreBoardID = _sceneStateMachine.Add(scoreBoardScene);

				// Game scenes need to know pauseScene, when pauseScene want to know current playing scene
				gameScene1->SetPauseScene(pauseScene);
				gameScene2->SetPauseScene(pauseScene);

				// Scene can be switched from game scene
				pauseScene->SetSwitchToScene({
					{ "LoadGameScene", loadGameSceneID }
				});
				gameScene1->SetSwitchToScene({
					{ "SceneGameOver", gameOverSceneID},
					{ "PauseScene", pauseSceneID }
				});
				gameScene2->SetSwitchToScene({
					{ "SceneGameOver", gameOverSceneID},
					{ "PauseScene", pauseSceneID }
				});

				switch (listitem) {
				case 0: 
					gameOverScene->SetSwitchToScene({
						{ "SceneGame", gameSceneID1}
					});
					_sceneStateMachine.SwitchTo(gameScene1);
					break;
				case 1:
					gameOverScene->SetSwitchToScene({
						{ "SceneGame", gameSceneID2}
					});
					_sceneStateMachine.SwitchTo(gameScene2);
					break;
				case 2:
					_sceneStateMachine.SwitchTo(loadGameScene);
					break;
				case 3: 
					ShopScene->SetSwitchToScene({ {"MainMenuScene", 0} });
					_sceneStateMachine.SwitchTo(ShopScene);
					break;
				case 4:
					scoreBoardScene->SetSwitchToScene({ { "MainMenuScene" , 0 } });
					_sceneStateMachine.SwitchTo(scoreBoardScene);
					break;
				case 5:
					exit(0);
					break;
				}
			},
			std::placeholders::_1
		)
	);
}

void SceneMainMenu::OnActivate() {
	mainMenu->OnActivate();
}

void SceneMainMenu::OnDeactivate()
{
	// Clear map
	mainMenu->OnDeactivate();
}

void SceneMainMenu::Update() {
	mainMenu->ProcessInput();
}

void SceneMainMenu::OnDestroy()
{
	// Clear map
	mainMenu->OnDeactivate();
}
