#pragma once

#include "GUI.h"

class FinishMenu
{
private:
	sf::Font& font;
	sf::Text text;
	sf::Text scoreText;

	sf::RectangleShape background;
	sf::RectangleShape container;
	std::map<std::string, gui::Button*> buttons;

	gui::TextField* field = nullptr;

public:
	FinishMenu(sf::VideoMode& videoMode, sf::Font& _font);
	virtual ~FinishMenu();

	std::map<std::string, gui::Button*>& GetButtons();

	void SetScoreText(int value);
	std::string GetFieldText();

	void AddButton(std::string key, std::string _text, int charSize, float width, float height, float y);
	bool IsButtonPressed(std::string key);

	void RenderButtons(sf::RenderTarget& target);
	void RenderGUI(sf::RenderTarget& target);
	void UpdateSFMLEvents(sf::Event& event);
	void Update(sf::Vector2i& mousePosition, const float& deltaTime);
	void Render(sf::RenderTarget& target);
};

