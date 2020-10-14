#pragma once
#include "SceneStateMachine.h"

const int SCREEN_WIDTH = 120;
const int SCREEN_HEIGHT = 40;

class Game
{
public:
    Game();

    void ProcessInput();
    void Update();
	void LateUpdate();
    void Draw();
    bool IsRunning() const;

private:
    SceneStateMachine sceneStateMachine; // New

    bool running;
};