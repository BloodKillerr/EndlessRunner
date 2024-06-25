#pragma once
#include "Enemy.h"
class Spike : public Enemy
{
private:
	sf::Texture spriteSheet;
	void InitTexture();

	sf::Vector2f velocity;

public:
	Spike(float x, float y, float scaleX, float scaleY);
	virtual ~Spike();

	virtual bool Attack(sf::FloatRect frect);

	virtual void Update(const float& deltaTime);
	virtual void Render(sf::RenderTarget& target, bool showHitbox = false);
};

