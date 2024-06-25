#include "PCH.h"
#include "FinishMenu.h"

FinishMenu::FinishMenu(sf::VideoMode& videoMode, sf::Font& _font) : font(_font)
{
	background.setSize(sf::Vector2f((float)videoMode.width, (float)videoMode.height));
	background.setFillColor(sf::Color(20, 20, 20, 100));
	container.setSize(sf::Vector2f(videoMode.width / 4.f, videoMode.height - gui::percentToPixelsY(9.26, videoMode)));
	container.setFillColor(sf::Color(20, 20, 20, 200));
	container.setPosition(videoMode.width / 2.f - container.getSize().x / 2.f, gui::percentToPixelsY(4.63, videoMode));

	text.setFont(font);
	text.setFillColor({ 235,148,20,255 });
	text.setCharacterSize(gui::calculateTextSize(45, videoMode));
	text.setString("FINISHED!");
	text.setPosition(container.getPosition().x + container.getSize().x / 2.f - text.getGlobalBounds().width / 2.f, container.getPosition().y + gui::percentToPixelsY(1.85, videoMode));

	scoreText.setFont(font);
	scoreText.setFillColor({ 235,148,20,255 });
	scoreText.setCharacterSize(gui::calculateTextSize(60, videoMode));
	scoreText.setString("Score:");
	scoreText.setPosition(container.getPosition().x + container.getSize().x / 2.f - text.getGlobalBounds().width / 2.f, container.getPosition().y + gui::percentToPixelsY(9.26, videoMode));

	field = new gui::TextField(container.getPosition().x + container.getSize().x / 2.f - gui::percentToPixelsX(10.4f, videoMode) / 2.f, container.getPosition().y + gui::percentToPixelsY(37.04, videoMode), gui::percentToPixelsX(10.4f, videoMode), gui::percentToPixelsY(9.26f, videoMode), font, gui::calculateTextSize(100, videoMode));
}

FinishMenu::~FinishMenu()
{
	for (auto it = buttons.begin(); it != buttons.end(); it++)
	{
		delete it->second;
	}

	delete field;
}

std::map<std::string, gui::Button*>& FinishMenu::GetButtons()
{
	return buttons;
}

void FinishMenu::SetScoreText(int value)
{
	std::string temp = "Score: " + std::to_string(value);
	scoreText.setString(temp);
}

std::string FinishMenu::GetFieldText()
{
	return field->GetText();
}

void FinishMenu::AddButton(std::string key, std::string _text, int charSize, float width, float height, float y)
{
	float x = container.getPosition().x + container.getSize().x / 2.f - width / 2.f;
	buttons[key] = new gui::Button(x, y, width, height, _text, &font, charSize, { 235,148,20,255 }, { 23,52,55,255 }, { 32,72,77,255 }, { 43,96,102,255 });
}

bool FinishMenu::IsButtonPressed(std::string key)
{
	return buttons[key]->IsPressed();
}

void FinishMenu::RenderButtons(sf::RenderTarget& target)
{
	for (auto& it : buttons)
	{
		it.second->Render(target);
	}
}

void FinishMenu::RenderGUI(sf::RenderTarget& target)
{
	RenderButtons(target);
	field->Render(target);
}

void FinishMenu::UpdateSFMLEvents(sf::Event& event)
{
	field->UpdateTextInput(event);
}

void FinishMenu::Update(sf::Vector2i& mousePosition, const float& deltaTime)
{
	for (auto& i : buttons)
	{
		i.second->Update(mousePosition);
	}

	field->Update(mousePosition, deltaTime);
}

void FinishMenu::Render(sf::RenderTarget& target)
{
	target.draw(background);
	target.draw(container);
	target.draw(text);
	target.draw(scoreText);
	RenderGUI(target);
}
