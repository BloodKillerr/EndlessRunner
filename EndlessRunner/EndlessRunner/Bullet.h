#pragma once
#include "Enemy.h"
class Bullet : public Enemy
{
private:
	sf::Texture spriteSheet;
	void InitTexture();

	sf::Vector2f velocity;

public:
	Bullet(float x, float y, float scaleX, float scaleY);
	virtual ~Bullet();

	virtual bool Attack(sf::FloatRect frect);

	virtual void Update(const float& deltaTime);
	virtual void Render(sf::RenderTarget& target, bool showHitbox = false);
};

