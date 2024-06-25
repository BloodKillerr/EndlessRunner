#pragma once

#include "GUI.h"

class PauseMenu
{
private:
	sf::Font& font;
	sf::Text text;

	sf::RectangleShape background;
	sf::RectangleShape container;
	std::map<std::string, gui::Button*> buttons;

public:
	PauseMenu(sf::VideoMode& videoMode, sf::Font& _font);
	virtual ~PauseMenu();

	std::map<std::string, gui::Button*>& GetButtons();

	void AddButton(std::string key, std::string _text, int charSize, float width, float height, float y);
	bool IsButtonPressed(std::string key);

	void RenderButtons(sf::RenderTarget& target);
	void RenderGUI(sf::RenderTarget& target);
	void Update(sf::Vector2i& mousePosition);
	void Render(sf::RenderTarget& target);
};

