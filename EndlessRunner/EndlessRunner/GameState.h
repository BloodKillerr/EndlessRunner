 #pragma once

#include "State.h"
#include "PauseMenu.h"
#include "FinishMenu.h"
#include "TileMap.h"
#include "LeaderBoardState.h"
#include "MapGeneratorComponent.h"
#include "ScoreTimerComponent.h"

class GameState : public State
{
private:
	sf::View mainView;
	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;

	sf::Font font;
	PauseMenu* pauseMenu;
	FinishMenu* finishMenu;
	Player* player;

	sf::Text scoreText;

	bool finished = false;

	float playerJumpTimer = 0.f;
	float playerMaxJumpTime = .45f;
	bool playerCanJump = true;
	bool playerJumping = false;

	sf::Vector2f maxSizeWorld;

	MapGeneratorComponent* mapGeneratorComponent = nullptr;
	ScoreTimerComponent* scoreTimerComponent = nullptr;

	void InitDeferredRender();
	void InitView();
	void InitWorldSize();
	void InitFonts();
	void InitKeybinds();
	void InitTextures();
	void InitPauseMenu();
	void InitFinishMenu();
	void InitPlayer();
	void InitScoreText();

	void CreateMapGeneratorComponent();
	void CreateScoreTimerComponent();

public:
	GameState(StateData* stateData);
	virtual ~GameState();

	void UpdateCollision(Entity* entity);

	void EndGame();

	void UpdateSFMLEvents(sf::Event& event);
	void Update(const float& deltaTime);
	void Render(sf::RenderTarget* target = nullptr);
	void UpdatePauseMenuButtons();
	void UpdateFinishMenuButtons();
	void UpdatePlayerInput(const float& deltaTime);
	void UpdateInput(const float& deltaTime);
};

