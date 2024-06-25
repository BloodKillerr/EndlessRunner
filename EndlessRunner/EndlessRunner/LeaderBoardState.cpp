#include "PCH.h"
#include "LeaderBoardState.h"

void LeaderBoardState::InitTitleText()
{
	sf::VideoMode& videoMode = stateData->GraphicsSettings->Resolution;
	titleText.setPosition(gui::percentToPixelsX(37.8125f, videoMode), gui::percentToPixelsY(5.f, videoMode));
	titleText.setFont(font);
	titleText.setCharacterSize(gui::calculateTextSize(36, videoMode));
	titleText.setFillColor({ 217,62,38,255 });
	titleText.setString("Top 10 Scores");
}

void LeaderBoardState::InitBackground()
{
	background.setSize(sf::Vector2f((float)window->getSize().x, (float)window->getSize().y));
	if (!backgroundTexture.loadFromFile("Resources/GFX/MainMenu/BG.png"))
	{
		throw("LeaderBoardState: Could not load background texture!");
	}
	background.setTexture(&backgroundTexture);
}

void LeaderBoardState::InitFonts()
{
	if (!font.loadFromFile("Fonts/NewRocker-Regular.ttf"))
	{
		throw("LeaderBoardState: Could not load font!");
	}
}

void LeaderBoardState::InitKeybinds()
{

}

void LeaderBoardState::InitButtons()
{
	sf::VideoMode& videoMode = stateData->GraphicsSettings->Resolution;
	buttons["ExitStateButton"] = new gui::Button(gui::percentToPixelsX(44.8f, videoMode), gui::percentToPixelsY(90.f, videoMode), gui::percentToPixelsX(10.4f, videoMode), gui::percentToPixelsY(6.94f, videoMode), "Quit", &font, gui::calculateTextSize(100, videoMode), { 235,148,20,255 }, { 23,52,55,255 }, { 32,72,77,255 }, { 43,96,102,255 });
}

void LeaderBoardState::InitGUI()
{
	InitTitleText();
	InitButtons();
}

void LeaderBoardState::InitPlaces()
{
	sf::VideoMode& videoMode = stateData->GraphicsSettings->Resolution;
	auto first_10 = scores | std::views::take(10);

	for (int i = 0; i < first_10.size(); i++)
	{
		sf::Text temp;
		temp.setPosition(gui::percentToPixelsX(39.f, videoMode), 100.f + gui::percentToPixelsY(30.f*(i+1)/5.f, videoMode));
		temp.setFont(font);
		temp.setCharacterSize(gui::calculateTextSize(70 + i*2, videoMode));
		temp.setFillColor({ 235,148,20,255 });
		temp.setString(std::to_string(i+1) + ". " + first_10[i].first + ": " + std::to_string(first_10[i].second));
		places.push_back(temp);
	}
}

void LeaderBoardState::RenderDebugPosition(sf::RenderTarget* target)
{
	sf::Text mousePositionText;
	mousePositionText.setPosition(mousePositionView.x, mousePositionView.y - 50.f);
	mousePositionText.setFont(font);
	mousePositionText.setCharacterSize(24);
	std::stringstream ss;
	ss << mousePositionView.x << " " << mousePositionView.y;
	mousePositionText.setString(ss.str());
	target->draw(mousePositionText);
}

LeaderBoardState::LeaderBoardState(StateData* stateData) : State(stateData)
{
	InitBackground();
	InitFonts();
	InitKeybinds();
	InitGUI();

	sf::Thread loadThread([this]() {
		this->LoadFromFile();
		});
	loadThread.launch();

	//LoadFromFile();
}

LeaderBoardState::~LeaderBoardState()
{
	for (auto it = buttons.begin(); it != buttons.end(); it++)
	{
		delete it->second;
	}
}

void LeaderBoardState::LoadFromFile()
{
	if (!std::filesystem::exists("Resources/Scores"))
	{
		std::filesystem::create_directories("Resources/Scores");
	}

	std::ifstream in("Resources/Scores/Scores.txt");

	if (in)
	{
		std::string temp = "";
		while (std::getline(in, temp))
		{
			std::smatch match;
			if (std::regex_match(temp, match, pattern))
			{
				std::pair data(match[1], std::stoi(match[2]));
				scores.push_back(data);
			}
			else
			{
				in.close();
				scores.clear();
				std::filesystem::remove("Resources/Scores/Scores.txt");
			}
		}

		InitPlaces();

		in.close();
	}
}

void LeaderBoardState::UpdateSFMLEvents(sf::Event& event)
{

}

void LeaderBoardState::Update(const float& deltaTime)
{
	UpdateInput(deltaTime);
	UpdateMousePositions();
	UpdateGUI(deltaTime);
}

void LeaderBoardState::Render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = window;
	}

	target->draw(background);
	target->draw(titleText);
	RenderGUI(*target);
	//RenderDebugPosition(target);
}

void LeaderBoardState::RenderButtons(sf::RenderTarget& target)
{
	for (auto& it : buttons)
	{
		it.second->Render(target);
	}
}

void LeaderBoardState::RenderGUI(sf::RenderTarget& target)
{
	RenderButtons(target);

	for (auto& it : places)
	{
		target.draw(it);
	}
}

void LeaderBoardState::UpdateInput(const float& deltaTime)
{

}

void LeaderBoardState::UpdateButtons()
{
	for (auto& it : buttons)
	{
		it.second->Update(mousePositionWindow);
	}

	if (buttons["ExitStateButton"]->IsPressed())
	{
		EndState();
	}
}

void LeaderBoardState::UpdateGUI(const float& deltaTime)
{
	UpdateButtons();
}
