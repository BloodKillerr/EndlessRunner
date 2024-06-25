#pragma once

#include "Player.h"
#include "GraphicsSettings.h"

class State;

class StateData
{
public:
	float GridSize = 0.f;
	GraphicsSettings* GraphicsSettings = nullptr;
	sf::RenderWindow* Window = nullptr;
	std::map<std::string, int>* SupportedKeys = nullptr;
	std::stack<State*>* States = nullptr;

	StateData()
	{

	}
};

class State
{
private:

protected:
	StateData* stateData = nullptr;

	std::stack<State*>* states = nullptr;

	sf::RenderWindow* window = nullptr;

	std::map<std::string, int>* supportedKeys = nullptr;
	std::map<std::string, int> keybinds;

	bool quit = false;
	bool paused = false;
	float keyTime = 0.f;
	float keyTimeMax = 20.f;
	float gridSize;

	sf::Vector2i mousePositionScreen;
	sf::Vector2i mousePositionWindow;
	sf::Vector2f mousePositionView;
	sf::Vector2i mousePositionGrid;

	std::map<std::string, sf::Texture> textures;

	virtual void InitKeybinds() = 0;

public:
	State(StateData* _stateData);
	virtual ~State();

	bool GetKeyTime();
	bool& GetQuit();

	void EndState();
	void PauseState();
	void ResumeState();

	virtual void UpdateSFMLEvents(sf::Event& event) = 0;
	virtual void Update(const float& deltaTime) = 0;
	virtual void Render(sf::RenderTarget* target = nullptr) = 0;
	virtual void UpdateInput(const float& deltaTime) = 0;
	virtual void UpdateMousePositions(sf::View* view = nullptr);
	virtual void UpdateKeyTime(const float& deltaTime);
};

