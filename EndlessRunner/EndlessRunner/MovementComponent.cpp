#include "PCH.h"
#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& _sprite, float _maxVelocity, float _acceleration, float _deceleration, float _gravity) : sprite(_sprite)
{
	maxVelocity = _maxVelocity;
	acceleration = _acceleration;
	deceleration = _deceleration;
	gravity = _gravity;
}

MovementComponent::~MovementComponent()
{

}

float& MovementComponent::GetMaxVelocity()
{
	return maxVelocity;
}

sf::Vector2f& MovementComponent::GetVelocity()
{
	return velocity;
}

void MovementComponent::StopVelocity()
{
	velocity.x = 0.f;
	velocity.y = 0.f;
}

void MovementComponent::StopVelocityX()
{
	velocity.x = 0.f;
}

void MovementComponent::StopVelocityY()
{
	velocity.y = 0.f;
}

void MovementComponent::Move(const float& deltaTime, float x, float y)
{
	velocity.x += acceleration * x;

	velocity.y += acceleration * y;
}

void MovementComponent::Update(const float& deltaTime)
{
	if (velocity.x > 0.f)
	{
		if (velocity.x > maxVelocity)
		{
			velocity.x = maxVelocity;
		}

		velocity.x -= deceleration;
		if (velocity.x < 0.f)
		{
			velocity.x = 0.f;
		}
	}
	else if (velocity.x < 0.f)
	{
		if (velocity.x < -maxVelocity)
		{
			velocity.x = -maxVelocity;
		}

		velocity.x += deceleration;
		if (velocity.x > 0.f)
		{
			velocity.x = 0.f;
		}
	}

	if (velocity.y > 0.f)
	{
		if (velocity.y > maxVelocity)
		{
			velocity.y = maxVelocity;
		}

		velocity.y -= deceleration;
		if (velocity.y < 0.f)
		{
			velocity.y = 0.f;
		}
	}
	else if (velocity.y < 0.f)
	{
		if (velocity.y < -maxVelocity)
		{
			velocity.y = -maxVelocity;
		}

		velocity.y += deceleration;
		if (velocity.y > 0.f)
		{
			velocity.y = 0.f;
		}
	}

	velocity.y += gravity;
	
	sprite.move(velocity * deltaTime);
}
