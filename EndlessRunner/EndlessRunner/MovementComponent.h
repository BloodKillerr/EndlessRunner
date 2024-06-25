#pragma once

class MovementComponent
{
private:
	sf::Sprite& sprite;

	float maxVelocity = 100.f;
	float acceleration;
	float deceleration;

	float gravity = 50.f;

	sf::Vector2f velocity;

public:
	MovementComponent(sf::Sprite& _sprite, float _maxVelocity, float _acceleration, float _deceleration, float _gravity);
	virtual ~MovementComponent();

	float& GetMaxVelocity();
	sf::Vector2f& GetVelocity();
	void StopVelocity();
	void StopVelocityX();
	void StopVelocityY();

	void Move(const float& deltaTime, float x, float y);
	void Update(const float& deltaTime);
};