#include "PCH.h"
#include "TextureSelector.h"

gui::TextureSelector::TextureSelector(float x, float y, float width, float height, float _gridSize, sf::Texture* textureSheet, sf::Font& _font, std::string _text)
{
	bounds.setSize(sf::Vector2f(width, height));
	bounds.setPosition(x, y);
	bounds.setFillColor(sf::Color(50, 50, 50, 100));
	bounds.setOutlineThickness(1.f);
	bounds.setOutlineColor(sf::Color(255, 255, 255, 200));

	sheet.setTexture(*textureSheet);
	sheet.setPosition(x, y);

	if (sheet.getGlobalBounds().width > bounds.getGlobalBounds().width)
	{
		sheet.setTextureRect(sf::IntRect(0, 0, (int)bounds.getGlobalBounds().width, (int)sheet.getGlobalBounds().height));
	}

	if (sheet.getGlobalBounds().height > bounds.getGlobalBounds().height)
	{
		sheet.setTextureRect(sf::IntRect(0, 0, (int)sheet.getGlobalBounds().width, (int)bounds.getGlobalBounds().height));
	}

	gridSize = _gridSize;

	selector.setPosition(x, y);
	selector.setSize(sf::Vector2f(gridSize, gridSize));
	selector.setFillColor(sf::Color::Transparent);
	selector.setOutlineThickness(1.f);
	selector.setOutlineColor(sf::Color::Red);

	textureRect.width = (int)gridSize;
	textureRect.height = (int)gridSize;

	hideButton = new gui::Button(1810.f, 20.f, 64.f, 64.f, _text, &_font, 32, { 235,148,20,255 }, { 23,52,55,255 }, { 32,72,77,255 }, { 43,96,102,255 });
}

gui::TextureSelector::~TextureSelector()
{
	delete hideButton;
}

bool gui::TextureSelector::GetKeyTime()
{
	if (keyTime >= keyTimeMax)
	{
		keyTime = 0.f;
		return true;
	}
	return false;
}

bool& gui::TextureSelector::GetActive()
{
	return active;
}

sf::IntRect& gui::TextureSelector::GetTextureRect()
{
	return textureRect;
}

void gui::TextureSelector::UpdateKeyTime(const float& deltaTime)
{
	if (keyTime < keyTimeMax)
	{
		keyTime += 10.f * deltaTime;
	}
}

void gui::TextureSelector::Update(const float& deltaTime, sf::Vector2i& mousePositionWindow)
{
	UpdateKeyTime(deltaTime);
	hideButton->Update(mousePositionWindow);

	if (hideButton->IsPressed() && GetKeyTime())
	{
		hidden = !hidden;
	}

	if (!hidden)
	{
		active = false;
		if (bounds.getGlobalBounds().contains(sf::Vector2f(mousePositionWindow)))
		{
			active = true;
			mousePositionGrid.x = (unsigned)(mousePositionWindow.x - bounds.getPosition().x) / (unsigned)gridSize;
			mousePositionGrid.y = (unsigned)(mousePositionWindow.y - bounds.getPosition().y) / (unsigned)gridSize;
			selector.setPosition(bounds.getPosition().x + mousePositionGrid.x * gridSize, bounds.getPosition().y + mousePositionGrid.y * gridSize);

			textureRect.left = (int)(selector.getPosition().x - bounds.getPosition().x);
			textureRect.top = (int)(selector.getPosition().y - bounds.getPosition().y);
		}
	}
}

void gui::TextureSelector::Render(sf::RenderTarget& target)
{
	if (!hidden)
	{
		target.draw(bounds);
		target.draw(sheet);

		if (active)
		{
			target.draw(selector);
		}
	}

	hideButton->Render(target);
}
