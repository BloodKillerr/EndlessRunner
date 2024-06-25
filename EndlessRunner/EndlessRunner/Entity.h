#pragma once

#include "HitboxComponent.h"
#include "MovementComponent.h"
#include "AnimationComponent.h"

class Entity
{
private:

protected:
	sf::Sprite sprite;

	bool groundCheck = true;

	HitboxComponent* hitboxComponent = nullptr;
	MovementComponent* movementComponent = nullptr;
	AnimationComponent* animationComponent = nullptr;

public:
	Entity();
	virtual ~Entity();

	virtual const sf::Vector2f& GetPosition();
	virtual const sf::Vector2i GetGridPosition(int gridSizeI);
	virtual const sf::FloatRect GetGlobalBounds();
	virtual const sf::FloatRect GetNextPositionBounds(const float& deltaTime);

	bool GetGroundCheck();

	void SetTexture(sf::Texture& _texture);
	void SetScale(float scaleX, float scaleY);
	void SetGroundCheck(bool value);

	void CreateHitboxComponent(float x, float y, float width, float height);
	void CreateMovementComponent(float _maxVelocity, float acceleration, float deceleration, float gravity);
	void CreateAnimationComponent(sf::Texture& _spriteSheet);

	virtual void SetPosition(float x, float y);
	virtual void Move(const float& deltaTime, const float x, const float y);

	virtual void StopVelocity();
	virtual void StopVelocityX();
	virtual void StopVelocityY();

	virtual void Update(const float& deltaTime) = 0;
	virtual void Render(sf::RenderTarget& target, bool showHitbox = false) = 0;
};