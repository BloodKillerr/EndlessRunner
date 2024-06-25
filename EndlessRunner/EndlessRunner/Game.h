#pragma once

#include "MainMenuState.h"

class Game
{
private:
	
	GraphicsSettings graphicsSettings;
	StateData stateData;
	sf::RenderWindow *window = nullptr;
	sf::Event event;

	sf::Clock deltaTimeClock;
	float deltaTime = 0.f;

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;

	float gridSize = 64.f;

	void InitGraphicsSettings();
	void InitWindow();
	void InitKeys();
	void InitStateData();
	void InitStates();
	
public:
	Game();
	virtual ~Game();

	void ApplicationQuit();

	void Update();
	void UpdateSFMLEvents();
	void UpdateDeltaTime();
	void Render();
	void Run();
};

