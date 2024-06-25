#pragma once

#include "Entity.h"

enum PlayerState
{
	RUN = 0,
	JUMP,
	FALL,
};

class Player : public Entity
{
private:
	PlayerState playerState = PlayerState::RUN;

	void InitComponenets();

public:
	Player(sf::Texture& _spriteSheet, float x, float y, float scaleX, float scaleY);
	virtual ~Player();

	sf::Vector2f& GetVelocity();
	void SetPlayerState(PlayerState state);

	void UpdateAnimation(const float& deltaTime);
	virtual void Update(const float& deltaTime);
	virtual void Render(sf::RenderTarget& target, bool showHitbox = false);
};