#include "PCH.h"
#include "Bullet.h"

void Bullet::InitTexture()
{
	if (!spriteSheet.loadFromFile("Resources/GFX/Turret/BulletSheet.png"))
	{
		throw("GameState: Could not load bullet texture!");
	}
}

Bullet::Bullet(float x, float y, float scaleX, float scaleY)
{
	InitTexture();

	SetPosition(x - (64.f * (scaleX - 1.f)), y - (64.f * (scaleY - 1.f)));
	SetScale(scaleX, scaleY);

	CreateHitboxComponent(49.f, 67.f, 15.f * scaleX, 20.f * scaleY);
	CreateAnimationComponent(spriteSheet);

	animationComponent->AddAnimation("IDLE", 50.f, 0, 0, 3, 0, 64, 64);

	velocity = sf::Vector2f(-1000.f, 0.f);
}

Bullet::~Bullet()
{

}

bool Bullet::Attack(sf::FloatRect frect)
{
	if (hitboxComponent->CheckIntersect(frect))
	{
		return true;
	}

	return false;
}

void Bullet::Update(const float& deltaTime)
{
	UpdateAnimation(deltaTime);

	sprite.move(velocity * deltaTime);

	hitboxComponent->Update(deltaTime);
}

void Bullet::Render(sf::RenderTarget& target, bool showHitbox)
{
	target.draw(sprite);

	if (hitboxComponent && showHitbox)
	{
		hitboxComponent->Render(target);
	}
}
