#include "PCH.h"
#include "Spike.h"

void Spike::InitTexture()
{
	if (!spriteSheet.loadFromFile("Resources/GFX/Spikes/SpikesSheet.png"))
	{
		throw("GameState: Could not load spikes texture!");
	}
}

Spike::Spike(float x, float y, float scaleX, float scaleY)
{
	InitTexture();

	SetPosition(x - (64.f*(scaleX-1.f)), y-(64.f*(scaleY-1.f)));
	SetScale(scaleX, scaleY);

	CreateHitboxComponent(0.f, 0.f, 64.f * scaleX, 64.f * scaleY);
	CreateAnimationComponent(spriteSheet);

	animationComponent->AddAnimation("IDLE", 20.f, 0, 0, 3, 0, 64, 64);

	velocity = sf::Vector2f(-400.f, 0.f);
}

Spike::~Spike()
{

}

bool Spike::Attack(sf::FloatRect frect)
{
	if (hitboxComponent->CheckIntersect(frect))
	{
		return true;	
	}

	return false;
}

void Spike::Update(const float& deltaTime)
{
	UpdateAnimation(deltaTime);

	sprite.move(velocity * deltaTime);

	hitboxComponent->Update(deltaTime);
}

void Spike::Render(sf::RenderTarget& target, bool showHitbox)
{
	target.draw(sprite);

	if (hitboxComponent && showHitbox)
	{
		hitboxComponent->Render(target);
	}
}
