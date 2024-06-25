#include "PCH.h"
#include "Game.h"

void Game::InitGraphicsSettings()
{
	graphicsSettings.LoadFromFile("Config/graphics.ini");
}

void Game::InitStateData()
{
	stateData.Window = window;
	stateData.GraphicsSettings = &graphicsSettings;
	stateData.SupportedKeys = &supportedKeys;
	stateData.States = &states;
	stateData.GridSize = gridSize;
}

void Game::InitWindow()
{
	if (graphicsSettings.FullScreen)
	{
		window = new sf::RenderWindow(graphicsSettings.Resolution, graphicsSettings.Title, sf::Style::Fullscreen, graphicsSettings.ContextSettings);
	}
	else
	{
		window = new sf::RenderWindow(graphicsSettings.Resolution, graphicsSettings.Title, sf::Style::Titlebar | sf::Style::Close, graphicsSettings.ContextSettings);
	}
	
	window->setFramerateLimit(graphicsSettings.FrameRateLimit);
	window->setVerticalSyncEnabled(graphicsSettings.VSync);
}

void Game::InitKeys()
{
	std::ifstream in("Config/supported_keys.ini");

	if (in.is_open())
	{
		std::string key = "";
		int key_value = 0;

		while (in >> key >> key_value)
		{
			supportedKeys[key] = key_value;
		}
	}

	in.close();
}

void Game::InitStates()
{
	states.push(new MainMenuState(&stateData));
}

Game::Game()
{
	InitGraphicsSettings();
	InitWindow();
	InitKeys();
	InitStateData();
	InitStates();
}

Game::~Game()
{
	delete window;

	while (!states.empty())
	{
		delete states.top();
		states.pop();
	}
}

void Game::ApplicationQuit()
{
	window->close();
}

void Game::Update()
{
	UpdateSFMLEvents();

	if (!states.empty())
	{
		if (window->hasFocus())
		{
			states.top()->Update(deltaTime);
			states.top()->UpdateSFMLEvents(event);

			if (states.top()->GetQuit())
			{
				states.top()->EndState();
				delete states.top();
				states.pop();
			}
		}		
	}
	else
	{
		ApplicationQuit();
	}
}

void Game::UpdateSFMLEvents()
{
	while (window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window->close();
			break;

		default:
			break;
		}
	}
}

void Game::UpdateDeltaTime()
{
	deltaTime = deltaTimeClock.restart().asSeconds();
}

void Game::Render()
{
	window->clear();
	
	if (!states.empty())
	{
		states.top()->Render(window);
	}

	window->display();
}

void Game::Run()
{
	while (window->isOpen())
	{
		auto deltaTimeAsync = std::async(std::launch::async, &Game::UpdateDeltaTime, this);
		deltaTimeAsync.get();
		//UpdateDeltaTime();
		Update();
		Render();
	}
}