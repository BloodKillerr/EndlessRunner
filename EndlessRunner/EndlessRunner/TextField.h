#pragma once

#include "Button.h"

namespace gui
{
#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

	class TextField
	{
	private:
		float keyTime = 0.f;
		float keyTimeMax = 2.f;
		sf::Font& font;
		gui::Button* field = nullptr;

		bool typeText = false;

		std::string inputText = "Input";

	public:
		TextField(float x, float y, float width, float height, sf::Font& _font, int fontSize);
		virtual ~TextField();

		bool GetKeyTime();

		std::string GetText();

		void InputLogic(int character);

		void UpdateTextInput(sf::Event& event);
		void UpdateKeyTime(const float& deltaTime);
		void Update(sf::Vector2i& mousePosition, const float& deltaTime);
		void Render(sf::RenderTarget& target);
	};
}