#include "PCH.h"
#include "MainMenuState.h"

void MainMenuState::InitTitleText()
{
	sf::VideoMode& videoMode = stateData->GraphicsSettings->Resolution;
	titleText.setPosition(gui::percentToPixelsX(9.9f, videoMode), gui::percentToPixelsY(30.6f, videoMode));
	titleText.setFont(font);
	titleText.setCharacterSize(gui::calculateTextSize(45, videoMode));
	titleText.setFillColor({217,62,38,255});
	titleText.setString("Endless Runner");
}

void MainMenuState::InitBackground()
{
	background.setSize(sf::Vector2f((float)window->getSize().x, (float)window->getSize().y));
	if (!backgroundTexture.loadFromFile("Resources/GFX/MainMenu/BG.png"))
	{
		throw("MainMenuState: Could not load background texture!");
	}
	background.setTexture(&backgroundTexture);
}

void MainMenuState::InitFonts()
{
	if (!font.loadFromFile("Fonts/NewRocker-Regular.ttf"))
	{
		throw("MainMenuState: Could not load font!");
	}
}

void MainMenuState::InitKeybinds()
{
	std::ifstream in("Config/mainmenustate_keybinds.ini");

	if (in.is_open())
	{
		std::string key = "";
		std::string key1 = "";

		while (in >> key >> key1)
		{
			keybinds[key] = supportedKeys->at(key1);
		}
	}

	in.close();
}

void MainMenuState::InitButtons()
{
	sf::VideoMode& videoMode = stateData->GraphicsSettings->Resolution;
	buttons["GameStateButton"] = new gui::Button(gui::percentToPixelsX(15.625f, videoMode), gui::percentToPixelsY(42.6f, videoMode), gui::percentToPixelsX(10.4f, videoMode), gui::percentToPixelsY(6.94f, videoMode), "Play", &font, gui::calculateTextSize(100, videoMode), {235,148,20,255}, {23,52,55,255}, {32,72,77,255}, {43,96,102,255});
	buttons["LeaderBoardStateButton"] = new gui::Button(gui::percentToPixelsX(15.625f, videoMode), gui::percentToPixelsY(51.f, videoMode), gui::percentToPixelsX(10.4f, videoMode), gui::percentToPixelsY(6.94f, videoMode), "LeaderBoard", &font, gui::calculateTextSize(100, videoMode), { 235,148,20,255 }, { 23,52,55,255 }, { 32,72,77,255 }, { 43,96,102,255 });
	buttons["EditorStateButton"] = new gui::Button(gui::percentToPixelsX(15.625f, videoMode), gui::percentToPixelsY(59.3f, videoMode), gui::percentToPixelsX(10.4f, videoMode), gui::percentToPixelsY(6.94f, videoMode), "Editor", &font, gui::calculateTextSize(100, videoMode), { 235,148,20,255 }, { 23,52,55,255 }, { 32,72,77,255 }, { 43,96,102,255 });
	buttons["ExitStateButton"] = new gui::Button(gui::percentToPixelsX(15.625f, videoMode), gui::percentToPixelsY(68.f, videoMode), gui::percentToPixelsX(10.4f, videoMode), gui::percentToPixelsY(6.94f, videoMode), "Quit", &font, gui::calculateTextSize(100, videoMode), { 235,148,20,255 }, { 23,52,55,255 }, { 32,72,77,255 }, { 43,96,102,255 });
}

void MainMenuState::InitGUI()
{
	InitTitleText();
	InitButtons();

	sf::VideoMode& videoMode = stateData->GraphicsSettings->Resolution;
	textField = new gui::TextField(gui::percentToPixelsX(83.85f, videoMode), gui::percentToPixelsY(74.07f, videoMode), gui::percentToPixelsX(10.4f, videoMode), gui::percentToPixelsY(9.26f, videoMode), font, gui::calculateTextSize(100, videoMode));
}

void MainMenuState::ResestGUI()
{
	for (auto it = buttons.begin(); it != buttons.end(); it++)
	{
		delete it->second;
	}
	buttons.clear();

	playerDummy = nullptr;
	InitPlayerDummy();

	InitGUI();
}

void MainMenuState::InitTextures()
{
	if (!textures["Player"].loadFromFile("Resources/GFX/Player/PlayerSheet.png"))
	{
		throw("MainMenuState: Could not load player texture!");
	}
}

void MainMenuState::InitPlayerDummy()
{
	sf::VideoMode& videoMode = stateData->GraphicsSettings->Resolution;
	playerDummy = new PlayerDummy(textures["Player"], gui::percentToPixelsX(67.71f, videoMode), gui::percentToPixelsY(21.3f, videoMode), 4.f, 4.f);
}

void MainMenuState::RenderDebugPosition(sf::RenderTarget* target)
{
	sf::Text mousePositionText;
	mousePositionText.setPosition(mousePositionView.x, mousePositionView.y-50.f);
	mousePositionText.setFont(font);
	mousePositionText.setCharacterSize(24);
	std::stringstream ss;
	ss << mousePositionView.x << " " << mousePositionView.y;
	mousePositionText.setString(ss.str());
	target->draw(mousePositionText);
}

MainMenuState::MainMenuState(StateData* stateData) : State(stateData)
{
	InitBackground();
	InitFonts();
	InitKeybinds();
	InitGUI();
	InitTextures();
	InitPlayerDummy();
	ResestGUI();
}

MainMenuState::~MainMenuState()
{
	for (auto it = buttons.begin(); it != buttons.end(); it++)
	{
		delete it->second;
	}

	delete playerDummy;
	delete textField;
}

void MainMenuState::CheckAdminAccess()
{
	if (std::regex_match(textField->GetText(),adminPassword))
	{
		showEditorButton = true;
	}
	else
	{
		showEditorButton = false;
	}
}

void MainMenuState::UpdateSFMLEvents(sf::Event& event)
{
	textField->UpdateTextInput(event);
}

void MainMenuState::Update(const float& deltaTime)
{
	sf::Thread adminThread([this]() {
		this->CheckAdminAccess();
		});
	adminThread.launch();

	//CheckAdminAccess();
	UpdateInput(deltaTime);
	UpdateMousePositions();
	UpdateGUI(deltaTime);

	sf::Thread pDthread([this, deltaTime]() {
		playerDummy->Update(deltaTime);
		});
	pDthread.launch();

	//playerDummy->Update(deltaTime);
}

void MainMenuState::Render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = window;
	}

	target->draw(background);
	target->draw(titleText);
	RenderGUI(*target);

	playerDummy->Render(*target);
	//RenderDebugPosition(target);
}

void MainMenuState::RenderButtons(sf::RenderTarget& target)
{
	for (auto &it : buttons)
	{
		if (it.second->GetText() == "Editor")
		{
			if (showEditorButton)
			{
				it.second->Render(target);
			}
		}
		else
		{
			it.second->Render(target);
		}
	}
}

void MainMenuState::RenderGUI(sf::RenderTarget& target)
{
	RenderButtons(target);
	textField->Render(target);
}

void MainMenuState::UpdateInput(const float& deltaTime)
{
	
}

void MainMenuState::UpdateButtons()
{
	for (auto &it : buttons)
	{
		it.second->Update(mousePositionWindow);
	}

	if (buttons["GameStateButton"]->IsPressed())
	{
		states->push(new GameState(stateData));
	}

	if (buttons["LeaderBoardStateButton"]->IsPressed())
	{
		states->push(new LeaderBoardState(stateData));
	}

	if (buttons["EditorStateButton"]->IsPressed())
	{
		if (showEditorButton)
		{
			states->push(new EditorState(stateData));
		}
	}

	if (buttons["ExitStateButton"]->IsPressed())
	{
		EndState();
	}
}

void MainMenuState::UpdateGUI(const float& deltaTime)
{
	UpdateButtons();
	textField->Update(mousePositionWindow, deltaTime);
}
