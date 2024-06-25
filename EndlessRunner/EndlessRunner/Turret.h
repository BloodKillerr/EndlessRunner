#pragma once
#include "Enemy.h"
#include "Bullet.h"
class Turret : public Enemy
{
private:
	sf::Texture spriteSheet;
	void InitTexture();

	sf::Vector2f velocity;

	std::deque<Bullet*> bullets;

	float bulletTimer = 0.f;
	float bulletMaxTimer = 2.f;

	float expireMaxTimer = 1.;
	float expireTimer = expireMaxTimer;
	
public:
	Turret(float x, float y, float scaleX, float scaleY);
	virtual ~Turret();

	virtual bool Attack(sf::FloatRect frect);

	void UpdateBullets(const float& deltaTime);

	virtual void Update(const float& deltaTime);
	virtual void Render(sf::RenderTarget& target, bool showHitbox = false);
};

