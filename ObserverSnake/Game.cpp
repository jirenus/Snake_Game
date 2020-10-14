#include "Game.h"
#include "SceneMainMenu.h"

Game::Game() : running(true)
{
	std::shared_ptr<SceneMainMenu> mainMenuScene = std::make_shared<SceneMainMenu>(sceneStateMachine);

	// Add players profile
	sceneStateMachine.addPlayer(std::make_shared<Player>(SCREEN_WIDTH / 10)); // UI on the 9/10 of screen width
	sceneStateMachine.addPlayer(std::make_shared<Player>(SCREEN_WIDTH / 10 * 9)); // like player 1 but 1/10 screen width

	// Managing scene is hard, but manage its ID is a bit easier
	unsigned int mainMenuSceneID1 = sceneStateMachine.Add(mainMenuScene);

	sceneStateMachine.SwitchTo(mainMenuSceneID1);
}

void Game::ProcessInput()
{
	//Process Input by default
	sceneStateMachine.ProcessInput();
}

void Game::Update()
{
	sceneStateMachine.Update();
}

void Game::LateUpdate()
{
	sceneStateMachine.LateUpdate();
}

void Game::Draw()
{
	sceneStateMachine.Draw();
}

bool Game::IsRunning() const
{
	return running;
}
