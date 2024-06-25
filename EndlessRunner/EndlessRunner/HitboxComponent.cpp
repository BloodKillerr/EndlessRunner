#include "PCH.h"
#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(sf::Sprite& _sprite, float x, float y, float width, float height) : sprite(_sprite), offsetX(x), offsetY(y)
{
	nextPosition.left = 0.f;
	nextPosition.top = 0.f;
	nextPosition.width = width;
	nextPosition.height = height;

	hitbox.setPosition(sprite.getPosition().x + x, sprite.getPosition().y + y);
	hitbox.setSize(sf::Vector2f(width, height));
	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setOutlineThickness(-1.f);
	hitbox.setOutlineColor(sf::Color::Green);
}

HitboxComponent::~HitboxComponent()
{

}

const sf::Vector2f& HitboxComponent::GetPosition()
{
	return hitbox.getPosition();
}

const sf::FloatRect HitboxComponent::GetGlobalBounds()
{
	return hitbox.getGlobalBounds();
}

const sf::FloatRect& HitboxComponent::GetNextPosition(sf::Vector2f velocity)
{
	nextPosition.left = hitbox.getPosition().x + velocity.x;
	nextPosition.top = hitbox.getPosition().y + velocity.y;

	return nextPosition;
}

void HitboxComponent::SetPosition(sf::Vector2f& position)
{
	hitbox.setPosition(position);
	sprite.setPosition(position.x - offsetX, position.y - offsetY);
}

void HitboxComponent::SetPosition(float x, float y)
{
	hitbox.setPosition(x, y);
	sprite.setPosition(x - offsetX, y - offsetY);
}

bool HitboxComponent::CheckIntersect(sf::FloatRect& frect)
{
	return hitbox.getGlobalBounds().intersects(frect);
}

void HitboxComponent::Update(const float& deltaTime)
{
	hitbox.setPosition(sprite.getPosition().x + offsetX, sprite.getPosition().y + offsetY);
}

void HitboxComponent::Render(sf::RenderTarget& target)
{
	target.draw(hitbox);
}
