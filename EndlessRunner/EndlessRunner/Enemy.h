#pragma once
#include "Entity.h"
class Enemy : public Entity
{
private:
	virtual void InitTexture() = 0;

public:
	Enemy();
	virtual ~Enemy();

	virtual bool Attack(sf::FloatRect frect) = 0;

	void UpdateAnimation(const float& deltaTime);
	virtual void Update(const float& deltaTime) = 0;
	virtual void Render(sf::RenderTarget& target, bool showHitbox = false) = 0;
};