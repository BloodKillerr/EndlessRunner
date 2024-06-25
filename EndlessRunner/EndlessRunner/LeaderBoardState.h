#pragma once
#include "State.h"
#include "GUI.h"

class LeaderBoardState : public State
{
private:
	sf::Text titleText;
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, gui::Button*> buttons;

	std::vector<std::pair<std::string, int>> scores;
	std::vector<sf::Text> places;

	std::regex pattern{ "^([a-zA-Z]{1,5}) ([0-9]+)$" };

	void InitTitleText();
	void InitBackground();
	void InitFonts();
	void InitKeybinds();
	void InitButtons();
	void InitGUI();
	void InitPlaces();

	void RenderDebugPosition(sf::RenderTarget* target);

public:
	LeaderBoardState(StateData* stateData);
	virtual ~LeaderBoardState();

	void LoadFromFile();

	void UpdateSFMLEvents(sf::Event& event);
	void Update(const float& deltaTime);
	void Render(sf::RenderTarget* target = nullptr);
	void RenderButtons(sf::RenderTarget& target);
	void RenderGUI(sf::RenderTarget& target);
	void UpdateInput(const float& deltaTime);
	void UpdateButtons();
	void UpdateGUI(const float& deltaTime);
};

