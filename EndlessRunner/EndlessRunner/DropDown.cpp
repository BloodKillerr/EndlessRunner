#include "PCH.h"
#include "DropDown.h"

gui::DropDown::DropDown(float x, float y, float width, float height, sf::Font& _font, int fontSize, std::string _list[], int numberOfElements, int defaultIndex) : font(_font)
{
	activeItem = new gui::Button(x, y, width, height, _list[defaultIndex], &font, fontSize, { 235,148,20,255 }, { 23,52,55,255 }, { 32,72,77,255 }, { 43,96,102,255 });

	for (int i=0; i<numberOfElements; i++)
	{
		list.push_back(new gui::Button(x, y + (i + 1) * height, width, height, _list[i], &font, fontSize, {235,148,20,255}, {23,52,55,255}, {32,72,77,255}, {43,96,102,255}, i));
	}
}

gui::DropDown::~DropDown()
{
	delete activeItem;

	for (auto &i : list)
	{
		delete i;
	}
}

int& gui::DropDown::GetActiveItemID()
{
	return activeItem->GetID();
}

bool gui::DropDown::GetKeyTime()
{
	if (keyTime >= keyTimeMax)
	{
		keyTime = 0.f;
		return true;
	}
	return false;
}

void gui::DropDown::UpdateKeyTime(const float& deltaTime)
{
	if (keyTime < keyTimeMax)
	{
		keyTime += 10.f * deltaTime;
	}
}

void gui::DropDown::Update(sf::Vector2i& mousePosition, const float& deltaTime)
{
	UpdateKeyTime(deltaTime);
	activeItem->Update(mousePosition);

	if (activeItem->IsPressed() && GetKeyTime())
	{
		showList = !showList;
	}

	if (showList)
	{
		for (auto& i : list)
		{
			i->Update(mousePosition);

			if (i->IsPressed() && GetKeyTime())
			{
				showList = false;
				activeItem->SetText(i->GetText());
				activeItem->ResetTextPosition();
				activeItem->SetID(i->GetID());
			}
		}
	}
}

void gui::DropDown::Render(sf::RenderTarget& target)
{
	activeItem->Render(target);

	if (showList)
	{
		for (auto& i : list)
		{
			i->Render(target);
		}
	}
}
