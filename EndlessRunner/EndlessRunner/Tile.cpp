#include "PCH.h"
#include "Tile.h"

Tile::Tile()
{

}

Tile::Tile(float x, float y, float gridSizeF, sf::Texture& texture, sf::IntRect& textureRect, bool _collision, int _type, float smallOffsetX)
{
	shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	shape.setFillColor(sf::Color::White);
	shape.setPosition(x * gridSizeF + smallOffsetX, y * gridSizeF);
	shape.setTexture(&texture);
	shape.setTextureRect(textureRect);

	velocity = sf::Vector2f(-400.f, 0.f);

	collision = _collision;
	type = _type;
}

Tile::~Tile()
{

}

int& Tile::GetType()
{
	return type;
}

const sf::Vector2f& Tile::GetPosition()
{
	return shape.getPosition();
}

bool Tile::GetCollision()
{
	return collision;
}

sf::FloatRect Tile::GetGlobalBounds()
{
	return shape.getGlobalBounds();
}

const sf::FloatRect Tile::GetNextGlobalBounds(const float& deltaTime)
{
	sf::FloatRect tempRect;
	tempRect.width = shape.getSize().x;
	tempRect.height = shape.getSize().y;
	tempRect.left = shape.getPosition().x + velocity.x * deltaTime;
	tempRect.top = shape.getPosition().y + velocity.y * deltaTime;

	return tempRect;
}

bool Tile::Intersects(sf::FloatRect bounds)
{
	return shape.getGlobalBounds().intersects(bounds);
}

bool Tile::Intersects(sf::FloatRect bounds, const float& deltaTime)
{
	return GetNextGlobalBounds(deltaTime).intersects(bounds);
}

std::string Tile::GetAsString()
{
	std::stringstream ss;
	ss << shape.getTextureRect().left << " " << shape.getTextureRect().top << " " << collision << " " << type;

	return ss.str();
}

void Tile::Update(const float& deltaTime)
{
	shape.move(velocity * deltaTime);
}

void Tile::Render(sf::RenderTarget& target)
{
	target.draw(shape);
}
