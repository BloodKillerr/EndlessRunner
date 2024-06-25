#include "PCH.h"
#include "GameState.h"

void GameState::InitDeferredRender()
{
	renderTexture.create(stateData->GraphicsSettings->Resolution.width, stateData->GraphicsSettings->Resolution.height);

	renderSprite.setTexture(renderTexture.getTexture());
	renderSprite.setTextureRect(sf::IntRect(0, 0, stateData->GraphicsSettings->Resolution.width, stateData->GraphicsSettings->Resolution.height));
}

void GameState::InitView()
{
	mainView.setSize(sf::Vector2f((float)stateData->GraphicsSettings->Resolution.width, (float)stateData->GraphicsSettings->Resolution.height));
	mainView.setCenter(sf::Vector2f((float)stateData->GraphicsSettings->Resolution.width / 2.f, (float)stateData->GraphicsSettings->Resolution.height / 2.f));
}

void GameState::InitWorldSize()
{
	maxSizeWorld.x = 1920.f;
	maxSizeWorld.y = 1080.f;
}

void GameState::InitFonts()
{
	if (!font.loadFromFile("Fonts/NewRocker-Regular.ttf"))
	{
		throw("MainMenuState: Could not load font!");
	}
}

void GameState::InitKeybinds()
{
	std::ifstream in("Config/gamestate_keybinds.ini");

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

void GameState::InitTextures()
{
	if (!textures["Player"].loadFromFile("Resources/GFX/Player/PlayerSheet.png"))
	{
		throw("GameState: Could not load player texture!");
	}
}

void GameState::InitPauseMenu()
{
	sf::VideoMode& videoMode = stateData->GraphicsSettings->Resolution;
	pauseMenu = new PauseMenu(videoMode, font);
	pauseMenu->AddButton("ResumeStateButton", "Resume", gui::calculateTextSize(100, videoMode), gui::percentToPixelsX(10.42f, videoMode), gui::percentToPixelsY(6.94f, videoMode), gui::percentToPixelsY(37.04f, videoMode));
	pauseMenu->AddButton("LeaderBoardStateButton", "LeaderBoard", gui::calculateTextSize(100, videoMode), gui::percentToPixelsX(10.42f, videoMode), gui::percentToPixelsY(6.94f, videoMode), gui::percentToPixelsY(55.56f, videoMode));
	pauseMenu->AddButton("QuitStateButton", "Quit", gui::calculateTextSize(100, videoMode), gui::percentToPixelsX(10.42f, videoMode), gui::percentToPixelsY(6.94f, videoMode), gui::percentToPixelsY(74.07f, videoMode));
}

void GameState::InitFinishMenu()
{
	sf::VideoMode& videoMode = stateData->GraphicsSettings->Resolution;
	finishMenu = new FinishMenu(videoMode, font);
	finishMenu->AddButton("SaveScoreButton", "Save", gui::calculateTextSize(100, videoMode), gui::percentToPixelsX(10.42f, videoMode), gui::percentToPixelsY(6.94f, videoMode), gui::percentToPixelsY(64.81f, videoMode));
	finishMenu->AddButton("QuitStateButton", "Quit", gui::calculateTextSize(100, videoMode), gui::percentToPixelsX(10.42f, videoMode), gui::percentToPixelsY(6.94f, videoMode), gui::percentToPixelsY(74.07f, videoMode));
}

void GameState::InitPlayer()
{
	player = new Player(textures["Player"], 896.f, 440.f, 1.f, 1.f);
}

void GameState::InitScoreText()
{
	sf::VideoMode& videoMode = stateData->GraphicsSettings->Resolution;

	scoreText.setFont(font);
	scoreText.setFillColor({ 235,148,20,255 });
	scoreText.setCharacterSize(gui::calculateTextSize(45, videoMode));
	scoreText.setString("0");
	scoreText.setPosition(gui::percentToPixelsX(2.6f, videoMode), gui::percentToPixelsY(2.6f, videoMode));
}

void GameState::CreateMapGeneratorComponent()
{
	mapGeneratorComponent = new MapGeneratorComponent(stateData->GridSize);
}

void GameState::CreateScoreTimerComponent()
{
	scoreTimerComponent = new ScoreTimerComponent();
}

GameState::GameState(StateData* stateData) : State(stateData)
{
	InitDeferredRender();
	InitView();
	InitWorldSize();
	InitFonts();
	InitKeybinds();
	InitTextures();
	InitPauseMenu();
	InitFinishMenu();
	InitPlayer();
	InitScoreText();

	CreateMapGeneratorComponent();
	CreateScoreTimerComponent();

	scoreTimerComponent->StartTimer();

	auto scoreTimerAsyncLoad = std::async(std::launch::async, &ScoreTimerComponent::LoadFromFile, scoreTimerComponent);
	scoreTimerAsyncLoad.get();

	//scoreTimerComponent->LoadFromFile();
}

GameState::~GameState()
{
	delete pauseMenu;
	delete finishMenu;
	delete player;
	delete mapGeneratorComponent;
	delete scoreTimerComponent;
}

void GameState::UpdateCollision(Entity* entity)
{
	if (entity->GetPosition().x < 0.f)
	{
		entity->SetPosition(0.f, entity->GetPosition().y);
		entity->StopVelocityX();
		EndGame();
	}
	else if (entity->GetPosition().x + entity->GetGlobalBounds().width > maxSizeWorld.x)
	{
		entity->SetPosition(maxSizeWorld.x - entity->GetGlobalBounds().width, entity->GetPosition().y);
		entity->StopVelocityX();
	}

	if (entity->GetPosition().y < 0.f)
	{
		entity->SetPosition(entity->GetPosition().x, 0.f);
		entity->StopVelocityY();
	}
	else if (entity->GetPosition().y + entity->GetGlobalBounds().height > maxSizeWorld.y)
	{
		entity->SetPosition(entity->GetPosition().x, maxSizeWorld.y - entity->GetGlobalBounds().height);
		entity->StopVelocityY();
	}
}

void GameState::EndGame()
{
	scoreTimerComponent->EndTimer();
	scoreText.setString(std::to_string(scoreTimerComponent->GetScore()));
	finishMenu->SetScoreText(scoreTimerComponent->GetScore());
	finished = true;
}

void GameState::UpdateSFMLEvents(sf::Event& event)
{
	if (finished)
	{
		finishMenu->UpdateSFMLEvents(event);
	}
}

void GameState::Update(const float& deltaTime)
{
	UpdateMousePositions(&mainView);
	UpdateKeyTime(deltaTime);

	if (!finished)
	{
		UpdateInput(deltaTime);
	}

	if (!paused)
	{

		if (finished)
		{
			finishMenu->Update(mousePositionWindow, deltaTime);
			UpdateFinishMenuButtons();
		}
		else
		{
			UpdatePlayerInput(deltaTime);

			UpdateCollision(player);

			mapGeneratorComponent->Update(player, deltaTime);

			if (mapGeneratorComponent->UpdateEnemyAttacks(player, deltaTime))
			{
				EndGame();
			}

			player->Update(deltaTime);

			auto scoreTimerComponentUpdateAsync = std::async(std::launch::async, &ScoreTimerComponent::Update, scoreTimerComponent, deltaTime);
			scoreTimerComponentUpdateAsync.get();

			scoreText.setString(std::to_string(scoreTimerComponent->GetScore()));
		}
	}
	else
	{
		pauseMenu->Update(mousePositionWindow);
		UpdatePauseMenuButtons();
	}
}

void GameState::Render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = window;
	}

	renderTexture.clear();

	renderTexture.setView(mainView);

	mapGeneratorComponent->Render(renderTexture);

	player->Render(renderTexture);

	mapGeneratorComponent->RenderDeferred(renderTexture);

	renderTexture.draw(scoreText);

	if (paused)
	{
		renderTexture.setView(renderTexture.getDefaultView());
		pauseMenu->Render(renderTexture);
	}

	if (finished)
	{
		renderTexture.setView(renderTexture.getDefaultView());
		finishMenu->Render(renderTexture);
	}

	renderTexture.display();
	renderSprite.setTexture(renderTexture.getTexture());
	target->draw(renderSprite);
}

void GameState::UpdatePauseMenuButtons()
{
	if (pauseMenu->IsButtonPressed("ResumeStateButton"))
	{
		ResumeState();
	}

	if (pauseMenu->IsButtonPressed("LeaderBoardStateButton"))
	{
		states->push(new LeaderBoardState(stateData));
	}

	if (pauseMenu->IsButtonPressed("QuitStateButton"))
	{
		EndState();
	}
}

void GameState::UpdateFinishMenuButtons()
{
	if (finishMenu->IsButtonPressed("SaveScoreButton"))
	{
		if (scoreTimerComponent->SaveToFile(finishMenu->GetFieldText(), scoreTimerComponent->GetScore()))
		{
			EndState();
		}
	}

	if (finishMenu->IsButtonPressed("QuitStateButton"))
	{
		EndState();
	}
}

void GameState::UpdatePlayerInput(const float& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds["JUMP"])) && playerCanJump)
	{
		player->Move(deltaTime, 0.f, -20.f);
		player->SetGroundCheck(false);
		playerJumping = true;
		player->SetPlayerState(PlayerState::JUMP);
	}
	else
	{
		playerJumping = false;
		player->SetPlayerState(PlayerState::FALL);
	}

	if (playerCanJump)
	{
		if (playerJumping)
		{
			playerJumpTimer += deltaTime;
		}

		if (playerJumpTimer >= playerMaxJumpTime)
		{
			playerCanJump = false;
			playerJumping = false;
		}
	}

	if (player->GetGroundCheck())
	{
		playerCanJump = true;
		playerJumping = false;
		playerJumpTimer = 0.f;
		player->SetPlayerState(PlayerState::RUN);
	}
}

void GameState::UpdateInput(const float& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds["CLOSE"])) && GetKeyTime())
	{
		if (paused)
		{
			ResumeState();
		}
		else
		{
			PauseState();
		}
	}
}
