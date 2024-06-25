#pragma once

class GraphicsSettings
{
private:

public:
	GraphicsSettings();
	virtual ~GraphicsSettings();

	std::string Title;
	sf::VideoMode Resolution;
	bool FullScreen;
	unsigned FrameRateLimit;
	bool VSync;
	sf::ContextSettings ContextSettings;
	std::vector<sf::VideoMode> VideoModes;

	void SaveToFile(std::string path);
	void LoadFromFile(std::string path);

};