#include "ScenePause.h"
#include "SceneSaveGame.h"

ScenePause::ScenePause(SceneStateMachine& sceneStateMachine) 
	: Scene(), _sceneStateMachine(sceneStateMachine), pauseMenu(nullptr), continueScene(0) {}

void ScenePause::SetContinueScene(std::shared_ptr<Scene> &prev)
{
	continueScene = prev;
}
void ScenePause::SetSwitchToScene(std::unordered_map<std::string, unsigned int> stateInf)
{
	// Stores the id of the scene that we will transition to.
	_stateInf.merge(stateInf);
}

void ScenePause::SwitchTo(std::string mapName)
{
	auto it = _stateInf.find(mapName);

	if (it != _stateInf.end()) {
		_sceneStateMachine.SwitchTo(it->second);
	}
}

void ScenePause::SwitchTo(std::shared_ptr<Scene> scene)
{
	_sceneStateMachine.SwitchTo(scene);
}

void ScenePause::OnCreate()
{
	pauseMenu = new Menu(
		{ L"Continue", L"Save game", L"Load game", L"Return to main menu" },
		std::bind(
			[this](unsigned int listitem) {
				switch (listitem) {
				case 0: {
					auto lastGameScene = continueScene;

					_sceneStateMachine.SwitchTo(lastGameScene);
					break;
				}
				case 1: {
					std::shared_ptr<SceneSaveGame> saveGameScene 
						= std::make_shared<SceneSaveGame>(_sceneStateMachine);

					saveGameScene->SetSwitchToScene({ 
						{ "ContinueScene", continueScene } 
					});

					//_currentGameScene = saveGameScene;
					//_currentGameScene->SetSaveGameScene(continueScene);

					saveGameScene->SetSaveGameScene(continueScene);

					SwitchTo(saveGameScene);
					break;
				}
				case 2: {
					SwitchTo("LoadGameScene");
					break;
				}
				case 3: {
					continueScene->OnCreate(); // reset old game sence when switching to choose map scene
					_sceneStateMachine.SwitchTo(0);
					break;
				}
				}

				//Console::TextColor(ColorCode_White);
				//Console::gotoXY(0, 0);
				//std::cout << "Select item: " << listitem << std::endl;
			},
			std::placeholders::_1
		)
	);
}

void ScenePause::OnActivate() {
	pauseMenu->OnActivate();
}

void ScenePause::OnDeactivate()
{
	// Clear map
	pauseMenu->OnDeactivate();
}

void ScenePause::ProcessInput() {
	pauseMenu->ProcessInput();
}

void ScenePause::OnDestroy()
{
	// Clear map
	pauseMenu->OnDeactivate();

	delete pauseMenu;
}
