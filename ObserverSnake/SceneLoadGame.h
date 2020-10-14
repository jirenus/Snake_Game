#pragma once
#include "Scene.h"
#include "Menu.h"
#include "SceneStateMachine.h"
#include "Snake.h"

class SceneLoadGame :
	public Scene
{
	friend class SceneStateMachine;
public:
	SceneLoadGame(SceneStateMachine& sceneStateMachine);

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

	// File list
	std::vector<std::wstring> files;
	
	// Data loaded
	std::vector<std::wstring> _maps;
	Coord _fruit;
	Coord _snakeHead;
	std::vector<Coord> _snakeSegments;
	unsigned int _currentRound;
	Direction _direction;

	Coord getFruit() { return _fruit; }
	Coord getSnakeHead() { return _snakeHead; }
	std::vector<Coord> getSnakeSegments() { return _snakeSegments; }
	unsigned int getCurrentRound() { return _currentRound; }
	Direction getDirection() { return _direction; }
};

