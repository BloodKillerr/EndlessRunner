#include "PCH.h"
#include "PlayerDummy.h"

void PlayerDummy::InitComponenets()
{

}

PlayerDummy::PlayerDummy(sf::Texture& _spriteSheet, float x, float y, float scaleX, float scaleY)
{
	SetPosition(x, y);
	SetScale(scaleX, scaleY);

	CreateAnimationComponent(_spriteSheet);
	animationComponent->AddAnimation("IDLE", 40.f, 0, 0, 7, 0, 64, 128);
}

PlayerDummy::~PlayerDummy()
{

}

void PlayerDummy::UpdateAnimation(const float& deltaTime)
{
	animationComponent->Play("IDLE", deltaTime);
}

void PlayerDummy::Update(const float& deltaTime)
{
	UpdateAnimation(deltaTime);
}

void PlayerDummy::Render(sf::RenderTarget& target, bool showHitbox)
{
	target.draw(sprite);

	if (hitboxComponent && showHitbox)
	{
		hitboxComponent->Render(target);
	}
}
