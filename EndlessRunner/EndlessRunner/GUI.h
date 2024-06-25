#pragma once

#include "Button.h"
#include "DropDown.h"
#include "TextureSelector.h"
#include "TextField.h"

namespace gui
{
	float percentToPixelsX(float percent, sf::VideoMode& videoMode);
	float percentToPixelsY(float percent, sf::VideoMode& videoMode);
	int calculateTextSize(int constant, sf::VideoMode& videoMode);
}