#include "SceneLoadGame.h"
#include "SceneGame.h"
#include "ScenePause.h"
#include "SceneGameOver.h"
#include <filesystem>
#include <sstream>

// Constructor de khi tao mot SceneLoadGame o Game.cpp
SceneLoadGame::SceneLoadGame(SceneStateMachine& sceneStateMachine)
	: Scene(), _sceneStateMachine(sceneStateMachine), gameOverMenu(nullptr) {}

// Cai nay de de~ dang nhan du lieu scene o Game.cpp
void SceneLoadGame::SetSwitchToScene(std::unordered_map<std::string, unsigned int> stateInf)
{
	// Stores the id of the scene that we will transition to.
	_stateInf.merge(stateInf);
}

void SceneLoadGame::SwitchTo(std::string mapName) // nay nhan vao mapName, la cai chuoi~ string dau tien
{
	auto it = _stateInf.find(mapName);

	if (it != _stateInf.end()) {
		_sceneStateMachine.SwitchTo(it->second);
	}
}

// Khi no duoc tao ra, ham nay chay cung voi constructor
void SceneLoadGame::OnCreate()
{
	auto path = std::filesystem::current_path();
	auto savegamePath = path;
	savegamePath += "\\savegames";

	std::filesystem::create_directory(savegamePath);

	// Top message
	Console::gotoXY(0, 0);
	Console::TextColor(ColorCode_Cyan);
	std::cout << "Choose a previous saved game to continue your progress." << std::endl;

	for (const auto& entry : std::filesystem::directory_iterator(savegamePath)) {
		files.push_back(entry.path().c_str());
	}
	
	auto menuItem{ files };
	menuItem.push_back(L"Back to main menu");

	// show menu that allow player to choose saved game file.
	gameOverMenu = new Menu(
		menuItem,
		std::bind(
			[this](unsigned int listitem, std::vector<std::wstring> writer) {
				if (listitem == writer.size()) {
					// Back to main menu
					_sceneStateMachine.SwitchTo(0);
				}
				else {
					// Load data from file
					std::wfstream f;
					f.open(writer[listitem], std::ios::in);

					if (!f.is_open()) {
						std::cout << "Can't open";
						Sleep(4000);
						exit(0);
					}
					// TODO: handle if file isn't exist
					int n;
					std::wstring mapName;

					// Map list
					f >> n;
					f.ignore(INT_MAX, '\n');

					for (int i = 0; i < n; i++) {
						getline(f, mapName);
						_maps.push_back(mapName);
					}

					// Skip \n
					//f.seekg(2, std::ios::cur);
					//getline(f, mapName);

					// Round
					f >> _currentRound;

					// Fruit coord
					f >> _fruit.X >> _fruit.Y;

					// Direction
					int x;
					f >> x;
					_direction = (Direction)x;

					// Snake/segments coord
					f >> _snakeHead.X >> _snakeHead.Y;

					_snakeSegments.push_back( { _snakeHead.X, _snakeHead.Y } );

					while (!f.eof()) {
						Coord a;
						f >> a.X >> a.Y;

						_snakeSegments.push_back(a);
					}

					// Close file
					f.close();

					// Initialize what a game scene needs
					std::shared_ptr<SceneGame> gameScene1 = std::make_shared<SceneGame>(1, _maps, _sceneStateMachine);
					unsigned int gameSceneID1 = _sceneStateMachine.Add(gameScene1);

					std::shared_ptr<ScenePause> pauseScene = std::make_shared<ScenePause>(_sceneStateMachine);
					std::shared_ptr<SceneGameOver> gameOverScene = std::make_shared<SceneGameOver>(_sceneStateMachine);

					unsigned int pauseSceneID = _sceneStateMachine.Add(pauseScene);
					unsigned int gameOverSceneID = _sceneStateMachine.Add(gameOverScene);

					gameScene1->initializeSavedData(getFruit(), getSnakeHead(), getSnakeSegments(), getCurrentRound(), getDirection());

					// Scene can be switched from game scene
					gameScene1->SetSwitchToScene({
						{ "SceneGameOver", gameOverSceneID},
						{ "PauseScene", pauseSceneID }
					});
					gameOverScene->SetSwitchToScene({
						{ "SceneGame", gameSceneID1 }
					});
					gameScene1->SetPauseScene(pauseScene);

					_sceneStateMachine.SwitchTo(gameSceneID1);

					// Remove scene when unused
					//_sceneStateMachine.Remove(gameSceneID1);
					//_sceneStateMachine.Remove(gameOverSceneID);
					//_sceneStateMachine.Remove(pauseSceneID);
				}
			},
			std::placeholders::_1, files
		)
	);
}

// Con may cai nay phai co de handle action cua menu
void SceneLoadGame::OnActivate() {
	gameOverMenu->OnActivate();
}

void SceneLoadGame::OnDeactivate()
{
	// Clear map
	gameOverMenu->OnDeactivate();
}

void SceneLoadGame::ProcessInput() {
	gameOverMenu->ProcessInput();
}

void SceneLoadGame::OnDestroy()
{
	// Clear map
	gameOverMenu->OnDeactivate();

	delete gameOverMenu;
}
