#include "PCH.h"
#include "Player.h"

void Player::InitComponenets()
{
	
}

Player::Player(sf::Texture& _spriteSheet, float x, float y, float scaleX, float scaleY)
{
	SetPosition(x, y);
	SetScale(scaleX, scaleY);

	CreateHitboxComponent(0.f, 20.f, 60.f*scaleX, 108.f*scaleY);
	CreateMovementComponent(600.f, 30.f, 5.f, 50.f);
	CreateAnimationComponent(_spriteSheet);

	animationComponent->AddAnimation("RUN", 20.f, 0, 1, 7, 1, 64, 128);
	animationComponent->AddAnimation("JUMP", 20.f, 0, 2, 7, 2, 64, 128);
	animationComponent->AddAnimation("FALL", 20.f, 0, 3, 7, 3, 64, 128);
}

Player::~Player()
{

}

sf::Vector2f& Player::GetVelocity()
{
	return movementComponent->GetVelocity();
}

void Player::SetPlayerState(PlayerState state)
{
	playerState = state;
}

void Player::UpdateAnimation(const float& deltaTime)
{
	switch (playerState)
	{
	case RUN:
		animationComponent->Play("RUN", deltaTime);
		break;
	case JUMP:
		animationComponent->Play("JUMP", deltaTime);
		break;
	case FALL:
		animationComponent->Play("FALL", deltaTime);
		break;
	default:
		break;
	}
}

void Player::Update(const float& deltaTime)
{
	movementComponent->Update(deltaTime);

	UpdateAnimation(deltaTime);

	hitboxComponent->Update(deltaTime);
}

void Player::Render(sf::RenderTarget& target, bool showHitbox)
{
	target.draw(sprite);

	if (hitboxComponent && showHitbox)
	{
		hitboxComponent->Render(target);
	}
}
