#pragma once

#include "Button.h"

namespace gui
{
	class TextureSelector
	{
	private:
		sf::RectangleShape bounds;
		sf::Sprite sheet;
		sf::RectangleShape selector;
		sf::Vector2u mousePositionGrid;
		sf::IntRect textureRect;
		float gridSize;
		bool active = false;
		bool hidden = true;
		float keyTime = 0.f;
		float keyTimeMax = 2.f;
		gui::Button* hideButton = nullptr;

	public:
		TextureSelector(float x, float y, float width, float height, float _gridSize, sf::Texture* textureSheet, sf::Font& _font, std::string _text);
		~TextureSelector();

		bool GetKeyTime();
		bool& GetActive();
		sf::IntRect& GetTextureRect();

		void UpdateKeyTime(const float& deltaTime);
		void Update(const float& deltaTime, sf::Vector2i& mousePositionWindow);
		void Render(sf::RenderTarget& target);

	};
}