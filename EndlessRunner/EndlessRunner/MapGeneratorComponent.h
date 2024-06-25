#pragma once
#include "TileMap.h"
class MapGeneratorComponent
{
private:
	std::deque<TileMap*> maps;
	float gridSizeF;

public:
	MapGeneratorComponent(float _gridSizeF = 64);
	virtual ~MapGeneratorComponent();

	void UpdateMaps(const float& deltaTime);
	bool UpdateEnemyAttacks(Entity* entity, const float& deltaTime);

	void Update(Entity* entity, const float& deltaTime);
	void Render(sf::RenderTarget& target);
	void RenderDeferred(sf::RenderTarget& target);
};