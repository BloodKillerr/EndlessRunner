#pragma once

class HitboxComponent
{
private:
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	sf::FloatRect nextPosition;
	float offsetX;
	float offsetY;

public:
	HitboxComponent(sf::Sprite& _sprite, float x, float y, float width, float height);
	virtual ~HitboxComponent();

	const sf::Vector2f& GetPosition();
	const sf::FloatRect GetGlobalBounds();
	const sf::FloatRect& GetNextPosition(sf::Vector2f velocity);

	void SetPosition(sf::Vector2f& position);
	void SetPosition(float x, float y);

	bool CheckIntersect(sf::FloatRect& frect);

	void Update(const float& deltaTime);
	void Render(sf::RenderTarget& target);
};

