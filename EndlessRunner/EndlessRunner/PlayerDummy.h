#pragma once

#include "Entity.h"

class PlayerDummy : public Entity
{
private:
	void InitComponenets();

public:
	PlayerDummy(sf::Texture& _spriteSheet, float x, float y, float scaleX, float scaleY);
	virtual ~PlayerDummy();

	void UpdateAnimation(const float& deltaTime);
	virtual void Update(const float& deltaTime);
	virtual void Render(sf::RenderTarget& target, bool showHitbox = false);
};

