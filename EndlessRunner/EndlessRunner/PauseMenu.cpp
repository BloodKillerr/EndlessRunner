#include "PCH.h"
#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::VideoMode& videoMode, sf::Font& _font) : font(_font)
{
	background.setSize(sf::Vector2f((float)videoMode.width, (float)videoMode.height));
	background.setFillColor(sf::Color(20, 20, 20, 100));
	container.setSize(sf::Vector2f(videoMode.width/4.f, videoMode.height - gui::percentToPixelsY(9.26 ,videoMode)));
	container.setFillColor(sf::Color(20, 20, 20, 200));
	container.setPosition(videoMode.width/2.f - container.getSize().x / 2.f, gui::percentToPixelsY(4.63, videoMode));

	text.setFont(font);
	text.setFillColor({ 235,148,20,255 });
	text.setCharacterSize(gui::calculateTextSize(45, videoMode));
	text.setString("PAUSED");
	text.setPosition(container.getPosition().x + container.getSize().x / 2.f - text.getGlobalBounds().width / 2.f, container.getPosition().y + gui::percentToPixelsY(1.85, videoMode));
}

PauseMenu::~PauseMenu()
{
	for (auto it = buttons.begin(); it != buttons.end(); it++)
	{
		delete it->second;
	}
}

std::map<std::string, gui::Button*>& PauseMenu::GetButtons()
{
	return buttons;
}

void PauseMenu::AddButton(std::string key, std::string _text, int charSize, float width, float height, float y)
{
	float x = container.getPosition().x + container.getSize().x / 2.f - width / 2.f;
	buttons[key] = new gui::Button(x, y, width, height, _text, &font, charSize, { 235,148,20,255 }, { 23,52,55,255 }, { 32,72,77,255 }, { 43,96,102,255 });
}

bool PauseMenu::IsButtonPressed(std::string key)
{
	return buttons[key]->IsPressed();
}

void PauseMenu::RenderButtons(sf::RenderTarget& target)
{
	for (auto& it : buttons)
	{
		it.second->Render(target);
	}
}

void PauseMenu::RenderGUI(sf::RenderTarget& target)
{
	RenderButtons(target);
}

void PauseMenu::Update(sf::Vector2i& mousePosition)
{
	for (auto& i : buttons)
	{
		i.second->Update(mousePosition);
	}
}

void PauseMenu::Render(sf::RenderTarget& target)
{
	target.draw(background);
	target.draw(container);
	target.draw(text);
	RenderGUI(target);
}
