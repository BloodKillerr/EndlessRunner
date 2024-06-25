#include "PCH.h"
#include "Button.h"

gui::Button::Button(float x, float y, float width, float height, std::string _text, sf::Font* _font, int fontSize, sf::Color fontColor, sf::Color _normalColor, sf::Color _hoverColor, sf::Color _pressedColor, int _id)
{
	shape.setPosition(sf::Vector2f(x, y));
	shape.setSize(sf::Vector2f(width, height));
	
	font = _font;
	text.setFont(*font);
	text.setString(_text);

	textColor = fontColor;

	text.setFillColor(textColor);
	text.setCharacterSize(fontSize);
	text.setPosition(
		shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) - text.getGlobalBounds().width / 2.f,
		shape.getPosition().y + (shape.getGlobalBounds().height / 2.f) - text.getGlobalBounds().height / 2.f
	);

	normalColor = _normalColor;
	hoverColor = _hoverColor;
	pressedColor = _pressedColor;

	shape.setFillColor(normalColor);
	id = _id;
}

gui::Button::~Button()
{
	
}

bool gui::Button::IsPressed()
{
	if (buttonState == buttonStates::PRESSED)
	{
		return true;
	}
	return false;
}

std::string gui::Button::GetText()
{
	return text.getString();
}

int& gui::Button::GetID()
{
	return id;
}

void gui::Button::SetText(std::string _text)
{
	text.setString(_text);
}

void gui::Button::SetID(int _id)
{
	id = _id;
}

void gui::Button::ResetTextPosition()
{
	text.setPosition(shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) - text.getGlobalBounds().width / 2.f, text.getPosition().y);
}

void gui::Button::Update(sf::Vector2i& mousePosition)
{
	buttonState = buttonStates::NORMAL;
	if (shape.getGlobalBounds().contains((sf::Vector2f)mousePosition))
	{
		buttonState = buttonStates::HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			buttonState = buttonStates::PRESSED;
		}
	}

	switch (buttonState)
	{
	case buttonStates::NORMAL:
		shape.setFillColor(normalColor);
		break;

	case buttonStates::HOVER:
		shape.setFillColor(hoverColor);
		break;

	case buttonStates::PRESSED:
		shape.setFillColor(pressedColor);
		break;

	default:
		shape.setFillColor(sf::Color::Red);
		break;
	}
}

void gui::Button::Render(sf::RenderTarget& target)
{
	target.draw(shape);
	target.draw(text);
}