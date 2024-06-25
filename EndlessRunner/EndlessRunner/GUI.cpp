#include "PCH.h"
#include "GUI.h"

float gui::percentToPixelsX(float percent, sf::VideoMode& videoMode)
{
	return std::floor(float(videoMode.width * (percent / 100.f)));
}

float gui::percentToPixelsY(float percent, sf::VideoMode& videoMode)
{
	return std::floor(float(videoMode.height * (percent / 100.f)));
}

int gui::calculateTextSize(int constant, sf::VideoMode& videoMode)
{
	return (videoMode.width + videoMode.height) / constant;
}