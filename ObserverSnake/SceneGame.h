#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <conio.h>
#include <bitset>

#include "Object.h"
#include "SnakeSegment.h"
#include "Snake.h"
#include "Fruit.h"
#include "Wall.h"
#include "Gate.h"
#include "Gift.h"

#include "SceneStateMachine.h"
#include "Scene.h"

class ScenePause;

class FileNotFoundException : public std::exception {
	const char* what() const noexcept {
		return "File not found";
	}
};

class NoSnakeException : public std::exception {
	const char* what() const noexcept {
		return "No snake position on map";
	}
};

enum class ObjectType {
	snake,
	snake_segment,
	wall,
	fruit,
	gate,
	gift
};

class SceneGame : public Scene, public std::enable_shared_from_this<SceneGame> {
	friend class Snake;
public:
	/* Which x, y is width/height of screen */
	static const short MAX_X = 130;
	static const short MAX_Y = 130;

private:
	// Game description
	unsigned int _currentRound; // start from 1
	unsigned int _lastRound;
	
	// Path to map (maybe contains 10 rounds/map)
	std::vector<std::wstring> _maps;

	// Current map attributes
	int _width;
	int _height;
	std::wstring _mapPath;

	// Position of the map on console screen
	Coord _position;

	// Map objects
	std::vector<std::shared_ptr<Object>> objects;

	std::vector<std::shared_ptr<Snake>> _snakes;
	std::shared_ptr<Fruit> _fruit;
	std::shared_ptr<Gate> _gate;

	// State switching
	std::unordered_map<std::string, unsigned int> _stateInf;
	SceneStateMachine& _sceneStateMachine;

	// Pause scene
	std::shared_ptr<ScenePause> _pauseScene;

	// Checking for free block
	std::bitset<MAX_X * MAX_Y> freeBlock;

	// Gift
	unsigned int _giftCount;

	unsigned int _playerNumber;
	// Set block occupied
	void setOccupiedBlock(int x, int y, unsigned int occupied = 1);

	// Some drawing
	void drawBorder();
	
public:
	SceneGame(const unsigned int playerNumber, const std::vector<std::wstring>& maps, SceneStateMachine& sceneStateMachine);

	void ShowTopTitle();

	// Scene switching
	void SetSwitchToScene(std::unordered_map<std::string, unsigned int> stateInf);
	void SetPauseScene(std::shared_ptr<ScenePause> scene) { _pauseScene = scene; }
	void SwitchTo(std::string mapName);

	// Just for one-player mode
	void initializeSavedData(Coord fruit, Coord snakeHead, std::vector<Coord> snakeSegments, unsigned int round, Direction dir);

	// Callbacks
	void OnCreate() override;
	void OnDestroy() override;

	void OnActivate() override;
	void OnDeactivate() override;
	void ProcessInput() override;
	void Update() override;
	void LateUpdate() override;
	
	void Draw() override;

	void drawSkillBox();

	// Addition functions
	Coord getFreeBlock();
	
	std::shared_ptr<Object> addObject(ObjectType type, int x, int y);
	
	void loadMap();
	void loadSnakeKeyHandle();

	bool isOccupied(int x, int y);

	void deleteSnakeSegment(int x, int y);
	void deleteFruit(int x, int y);

	int getWidth();
	int getHeight();

	std::vector<std::wstring> getMapPath() { return _maps; }
	std::shared_ptr<Fruit> getFruit() { return _fruit; }
	std::shared_ptr<Snake> getSnake() { return _snakes[0]; }

	unsigned int getCurrentRound() { return _currentRound; }

	void saveScore();
};