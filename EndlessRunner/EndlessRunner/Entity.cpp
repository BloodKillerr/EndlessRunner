#include "PCH.h"
#include "Entity.h"

Entity::Entity()
{
	
}

Entity::~Entity()
{
	delete hitboxComponent;
	delete movementComponent;
	delete animationComponent;
}

const sf::Vector2f& Entity::GetPosition()
{
	if (hitboxComponent)
	{
		return hitboxComponent->GetPosition();
	}
	return sprite.getPosition();
}

const sf::Vector2i Entity::GetGridPosition(int gridSizeI)
{
	if (hitboxComponent)
	{
		return sf::Vector2i((int)hitboxComponent->GetPosition().x / gridSizeI, (int)hitboxComponent->GetPosition().y / gridSizeI);
	}
	return sf::Vector2i((int)sprite.getPosition().x / gridSizeI, (int)sprite.getPosition().y / gridSizeI);
}

const sf::FloatRect Entity::GetGlobalBounds()
{
	if (hitboxComponent)
	{
		return hitboxComponent->GetGlobalBounds();
	}
	return sprite.getGlobalBounds();
}

const sf::FloatRect Entity::GetNextPositionBounds(const float& deltaTime)
{
	if (hitboxComponent && movementComponent)
	{
		return hitboxComponent->GetNextPosition(movementComponent->GetVelocity() * deltaTime);
	}
	return sf::FloatRect(-1.f, -1.f, -1.f, -1.f);
}

bool Entity::GetGroundCheck()
{
	return groundCheck;
}

void Entity::SetTexture(sf::Texture& _texture)
{
	sprite.setTexture(_texture);
}

void Entity::SetScale(float scaleX, float scaleY)
{
	sprite.setScale(scaleX, scaleY);
}

void Entity::SetGroundCheck(bool value)
{
	groundCheck = value;
}

void Entity::CreateHitboxComponent(float x, float y, float width, float height)
{
	hitboxComponent = new HitboxComponent(sprite, x, y, width, height);
}

void Entity::Update(const float& deltaTime)
{

}

void Entity::StopVelocity()
{
	if (movementComponent)
	{
		movementComponent->StopVelocity();
	}
}

void Entity::StopVelocityX()
{
	if (movementComponent)
	{
		movementComponent->StopVelocityX();
	}
}

void Entity::StopVelocityY()
{
	if (movementComponent)
	{
		movementComponent->StopVelocityY();
	}
}

void Entity::CreateMovementComponent(float _maxVelocity, float acceleration, float deceleration, float gravity)
{
	movementComponent = new MovementComponent(sprite, _maxVelocity, acceleration, deceleration, gravity);
}

void Entity::CreateAnimationComponent(sf::Texture& _spriteSheet)
{
	animationComponent = new AnimationComponent(sprite, _spriteSheet);
}

void Entity::SetPosition(float x, float y)
{
	if (hitboxComponent)
	{
		hitboxComponent->SetPosition(x, y);
	}
	else
	{
		sprite.setPosition(x, y);
	}	
}

void Entity::Move(const float& deltaTime, const float x, const float y)
{
	if (movementComponent)
	{
		movementComponent->Move(deltaTime, x, y);
	}
}