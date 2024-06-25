#pragma once

#include "MovementComponent.h"

enum TileType
{
	DEFAULT = 0,
	FRONT,
	SPIKE,
	TURRET
};

class Tile
{
private:

protected:
	sf::RectangleShape shape;
	bool collision = false;
	int type = 0;

	sf::Vector2f velocity;

public:
	Tile();
	Tile(float x, float y, float gridSizeF, sf::Texture& texture, sf::IntRect& textureRect, bool _collision = false, int _type = TileType::DEFAULT, float smallOffsetX = 0.f);
	virtual ~Tile();

	int& GetType();

	const sf::Vector2f& GetPosition();
	bool GetCollision();
	sf::FloatRect GetGlobalBounds();
	const sf::FloatRect GetNextGlobalBounds(const float& deltaTime);
	bool Intersects(sf::FloatRect bounds);
	bool Intersects(sf::FloatRect bounds, const float& deltaTime);
	std::string GetAsString();

	void Update(const float& deltaTime);
	void Render(sf::RenderTarget& target);
};

