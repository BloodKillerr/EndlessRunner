#include "PCH.h"
#include "TextField.h"

gui::TextField::TextField(float x, float y, float width, float height, sf::Font& _font, int fontSize) : font(_font)
{
	field = new gui::Button(x, y, width, height, inputText, &font, fontSize, { 235,148,20,255 }, { 23,52,55,255 }, { 32,72,77,255 }, { 43,96,102,255 });
}

gui::TextField::~TextField()
{
	delete field;
}

bool gui::TextField::GetKeyTime()
{
	if (keyTime >= keyTimeMax)
	{
		keyTime = 0.f;
		return true;
	}
	return false;
}

std::string gui::TextField::GetText()
{
	return inputText;
}

void gui::TextField::InputLogic(int character)
{
	switch (character)
	{
	case DELETE_KEY:
		if (inputText.length() > 0)
		{
			std::string temp = inputText;
			std::string newText = "";

			for (int i = 0; i < temp.length() - 1; i++)
			{
				newText += temp[i];
			}

			inputText = "";
			inputText = newText;
		}
		break;
	case ESCAPE_KEY:
		typeText = false;
		inputText = "Input";
		break;
	case ENTER_KEY:
		typeText = false;
		break;
	default:
		if (inputText.length() < 5)
		{
			inputText += char(character);
		}
		break;
	}

	field->SetText(inputText);
}

void gui::TextField::UpdateTextInput(sf::Event& event)
{
	if (typeText)
	{
		if (event.type == sf::Event::TextEntered && GetKeyTime())
		{
			if (event.text.unicode < 128)
			{
				InputLogic(event.text.unicode);
			}
		}
	}
}

void gui::TextField::UpdateKeyTime(const float& deltaTime)
{
	if (keyTime < keyTimeMax)
	{
		keyTime += 10.f * deltaTime;
	}
}

void gui::TextField::Update(sf::Vector2i& mousePosition, const float& deltaTime)
{
	UpdateKeyTime(deltaTime);
	field->Update(mousePosition);

	if (field->IsPressed() && GetKeyTime())
	{
		typeText = !typeText;
	}
}

void gui::TextField::Render(sf::RenderTarget& target)
{
	field->Render(target);
}
