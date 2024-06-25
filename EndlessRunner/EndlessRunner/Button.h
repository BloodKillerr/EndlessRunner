#pragma once

enum buttonStates
{
	NORMAL = 0,
	HOVER = 1,
	PRESSED = 2,
};

namespace gui
{
	class Button
	{
	private:
		int buttonState = buttonStates::NORMAL;
		int id = 0;

		bool pressed = false;
		bool hover = false;

		sf::RectangleShape shape;
		sf::Font* font = nullptr;
		sf::Text text;
		sf::Color textColor;

		sf::Color normalColor;
		sf::Color hoverColor;
		sf::Color pressedColor;

	public:
		Button(float x, float y, float width, float height, std::string _text, sf::Font* _font, int fontSize, sf::Color fontColor, sf::Color _normalColor, sf::Color _hoverColor, sf::Color _pressedColor, int _id = 0);
		virtual ~Button();

		bool IsPressed();
		std::string GetText();
		int& GetID();

		void SetText(std::string _text);
		void SetID(int _id);
		void ResetTextPosition();

		void Update(sf::Vector2i& mousePosition);
		void Render(sf::RenderTarget& target);
	};
}
