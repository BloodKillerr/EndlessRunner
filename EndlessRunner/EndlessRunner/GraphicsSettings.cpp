#include "PCH.h"
#include "GraphicsSettings.h"

GraphicsSettings::GraphicsSettings()
{
	Title = "Endless Runner";
	Resolution = sf::VideoMode::getDesktopMode();
	FullScreen = true;
	VSync = false;
	FrameRateLimit = 0;
	ContextSettings.antialiasingLevel = 0;
	VideoModes = sf::VideoMode::getFullscreenModes();
}

GraphicsSettings::~GraphicsSettings()
{

}

void GraphicsSettings::SaveToFile(std::string path)
{
	std::ofstream out(path);

	if (out)
	{
		out << Title;
		out << Resolution.width << " " << Resolution.height;
		out << FullScreen;
		out << FrameRateLimit;
		out << VSync;
		out << ContextSettings.antialiasingLevel;
	}
	out.close();
}

void GraphicsSettings::LoadFromFile(std::string path)
{
	{
		std::ifstream in(path);

		if (in)
		{
			std::getline(in, Title);
			in >> Resolution.width >> Resolution.height;
			in >> FullScreen;
			in >> FrameRateLimit;
			in >> VSync;
			in >> ContextSettings.antialiasingLevel;
		}
		in.close();
	}
}
