#pragma once
#include <memory>
#include <unordered_map>
#include"Player.h"
class Scene;
class SceneGame;

class SceneStateMachine
{
	friend class SceneGame;
public:
	SceneStateMachine();

	// ProcessInput, Update, LateUpdate, and Draw will simply be 
	// pass through methods. They will call the correspondingly 
	// named methods of the active scene.
	void ProcessInput();
	void Update();
	void LateUpdate();
	void Draw();

	// Adds a scene to the state machine and returns the id of that scene.
	unsigned int Add(std::shared_ptr<Scene> scene);

	// Transitions to scene with specified id.
	void SwitchTo(unsigned int id);
	void SwitchTo(std::shared_ptr<Scene>);

	// Removes scene from state machine.
	void Remove(unsigned int id);

	// Get current scene id
	std::shared_ptr<Scene>& GetCurrentScene() { return curScene; }

	// Player manager
	void addPlayer(std::shared_ptr<Player> player);
	std::shared_ptr<Player> getPlayer(int idx) { return _players[idx]; }

private:
	// Stores all of the scenes associated with this state machine.
	std::unordered_map<unsigned int, std::shared_ptr<Scene>> scenes;

	// Stores a reference to the current scene. Used when drawing/updating.
	std::shared_ptr<Scene> curScene;

	// Stores our current scene id. This is incremented whenever 
	// a scene is added.
	unsigned int insertedSceneID;

	//save id of curScene
	int curSceneID;

	//Player
	std::vector<std::shared_ptr<Player>> _players;
};

