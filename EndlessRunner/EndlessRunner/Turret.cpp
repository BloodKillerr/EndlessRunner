#include "PCH.h"
#include "Turret.h"

void Turret::InitTexture()
{
	if (!spriteSheet.loadFromFile("Resources/GFX/Turret/TurretSheet.png"))
	{
		throw("GameState: Could not load turret texture!");
	}
}

Turret::Turret(float x, float y, float scaleX, float scaleY)
{
	InitTexture();

	SetPosition(x - (64.f * (scaleX - 1.f)), y - (64.f * (scaleY - 1.f)));
	SetScale(scaleX, scaleY);

	CreateHitboxComponent(0.f, 48.f, 64.f * scaleX, 40.f * scaleY);
	CreateAnimationComponent(spriteSheet);

	animationComponent->AddAnimation("IDLE", 45.f, 0, 0, 3, 0, 64, 64);

	velocity = sf::Vector2f(-400.f, 0.f);
}

Turret::~Turret()
{

}

bool Turret::Attack(sf::FloatRect frect)
{
	for (auto& bullet : bullets)
	{
		if (bullet->Attack(frect))
		{
			return true;
		}
	}

	return false;
}

void Turret::UpdateBullets(const float& deltaTime)
{
	if (bulletTimer <= 0.f)
	{
		bullets.push_back(new Bullet(GetPosition().x, GetPosition().y + 16.f, 2.f, 2.f));
		bulletTimer = bulletMaxTimer;
	}
	else
	{
		bulletTimer -= deltaTime;
	}

	if (expireTimer <= 0.f)
	{
		delete bullets.front();
		bullets.pop_front();
		expireTimer = expireMaxTimer;
	}
	else if(bullets.size() == 1)
	{
		expireTimer -= deltaTime;
	}

	for (auto& bullet : bullets)
	{
		bullet->Update(deltaTime);
	}
}

void Turret::Update(const float& deltaTime)
{
	UpdateAnimation(deltaTime);

	sprite.move(velocity * deltaTime);

	hitboxComponent->Update(deltaTime);

	UpdateBullets(deltaTime);
}

void Turret::Render(sf::RenderTarget& target, bool showHitbox)
{
	target.draw(sprite);

	if (hitboxComponent && showHitbox)
	{
		hitboxComponent->Render(target);
	}

	for (auto& bullet : bullets)
	{
		bullet->Render(target, showHitbox);
	}
}
