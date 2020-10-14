#pragma once
#include "Scene.h"
#include "Menu.h"
#include "SceneStateMachine.h"

class SceneGameOver :
	public Scene
{
	friend class SceneStateMachine;
public:
	SceneGameOver(SceneStateMachine& sceneStateMachine);

	// Called when scene initially created. Called once.
	virtual void OnCreate();

	// Called when scene destroyed. Called at most once (if a scene 
	// is not removed from the game, this will never be called).
	virtual void OnDestroy();

	// Called whenever a scene is transitioned into. Can be 
	// called many times in a typical game cycle.
	virtual void OnActivate() override;

	// Called whenever a transition out of a scene occurs. 
	// Can be called many times in a typical game cycle.
	virtual void OnDeactivate() override;

	void SetSwitchToScene(std::unordered_map<std::string, unsigned int> stateInf);
	void SwitchTo(std::string mapName);

	// The below functions can be overridden as necessary in our scenes.
	virtual void ProcessInput() override;
private:
	Menu* gameOverMenu;

	SceneStateMachine& _sceneStateMachine;
	std::unordered_map<std::string, unsigned int> _stateInf;
};

