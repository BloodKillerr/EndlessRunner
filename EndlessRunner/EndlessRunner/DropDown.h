#pragma once

#include "Button.h"

namespace gui
{
	class DropDown
	{
	private:
		float keyTime = 0.f;
		float keyTimeMax = 2.f;
		sf::Font& font;
		gui::Button* activeItem = nullptr;
		std::vector<gui::Button*> list;

		bool showList = false;

	public:
		DropDown(float x, float y, float width, float height, sf::Font& _font, int fontSize, std::string _list[], int numberOfElements, int defaultIndex = 0);
		virtual ~DropDown();

		int& GetActiveItemID();

		bool GetKeyTime();

		void UpdateKeyTime(const float& deltaTime);
		void Update(sf::Vector2i& mousePosition, const float& deltaTime);
		void Render(sf::RenderTarget& target);
	};
}