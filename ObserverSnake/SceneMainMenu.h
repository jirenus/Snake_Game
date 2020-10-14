#pragma once
#include "Scene.h"
#include <vector>
#include <unordered_map>

class Menu;
class SceneStateMachine;

class SceneMainMenu : public Scene
{
private:
	Menu* mainMenu;
	SceneStateMachine& _sceneStateMachine;

	std::unordered_map<std::string, unsigned int> _stateInf;
public:
	SceneMainMenu(SceneStateMachine& sceneStateMachine);

	void SetSwitchToScene(std::unordered_map<std::string, unsigned int> stateInf);
	void SwitchTo(std::string mapName);

	void OnCreate() override;
	void OnActivate() override;
	void OnDeactivate() override;
	void Update() override;
	void OnDestroy() override;
};

