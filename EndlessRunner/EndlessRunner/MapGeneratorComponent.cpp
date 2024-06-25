#include "PCH.h"
#include "MapGeneratorComponent.h"

MapGeneratorComponent::MapGeneratorComponent(float _gridSizeF)
{
	gridSizeF = _gridSizeF;
	maps.push_back(new TileMap(10, 17, 0, gridSizeF, 1, "Resources/GFX/Tiles/TileSheet.png"));
	maps.push_back(new TileMap(10, 17, 10, gridSizeF, 1, "Resources/GFX/Tiles/TileSheet.png"));
	maps.push_back(new TileMap(10, 17, 20, gridSizeF, 1, "Resources/GFX/Tiles/TileSheet.png"));
	maps.push_back(new TileMap(10, 17, 30, gridSizeF, 1, "Resources/GFX/Tiles/TileSheet.png"));
	maps[0]->LoadFromFile("Resources/TileMaps/TileMap0.map", 0);
	maps[1]->LoadFromFile("Resources/TileMaps/TileMap1.map", 1);
	maps[2]->LoadFromFile("Resources/TileMaps/TileMap0.map", 2);
	maps[3]->LoadFromFile("Resources/TileMaps/TileMap1.map", 3);
}

MapGeneratorComponent::~MapGeneratorComponent()
{
	for (auto& map : maps)
	{
		delete map;
	}
}

void MapGeneratorComponent::UpdateMaps(const float& deltaTime)
{
	if (maps.size() == 5)
	{
		if (maps[0]->GetPosition(deltaTime).x <= -640.f)
		{
			float temp = maps[0]->GetPosition(deltaTime).x + 640.f;
			delete maps.front();
			maps.pop_front();

			std::random_device dev;
			std::mt19937 rng(dev());
			std::uniform_int_distribution<std::mt19937::result_type> dist(2, 15);

			int index = 0;

			do
			{
				index = dist(rng);
			} while (index == maps.back()->GetIndex());

			maps.push_back(new TileMap(10, 17, int(maps.size() * 10), gridSizeF, 1, "Resources/GFX/Tiles/TileSheet.png", 0, temp));
			maps.back()->LoadFromFile("Resources/TileMaps/TileMap" + std::to_string(index) + ".map", 0);	
		}
	}
	else
	{
		while (maps.size() < 5)
		{
			std::random_device dev;
			std::mt19937 rng(dev());
			std::uniform_int_distribution<std::mt19937::result_type> dist(0, 1);

			maps.push_back(new TileMap(10, 17, int(maps.size() * 10), gridSizeF, 1, "Resources/GFX/Tiles/TileSheet.png"));
			maps.back()->LoadFromFile("Resources/TileMaps/TileMap" + std::to_string(dist(rng)) + ".map", 0);
		}
	}
}

bool MapGeneratorComponent::UpdateEnemyAttacks(Entity* entity, const float& deltaTime)
{
	for (auto& map : maps)
	{
		if (map->UpdateEnemyAttacks(entity, deltaTime))
		{
			return true;
		}
	}

	return false;
}

void MapGeneratorComponent::Update(Entity* entity, const float& deltaTime)
{
	UpdateMaps(deltaTime);
	for (auto& map : maps)
	{
		map->UpdateCollision(entity, deltaTime);
		map->Update(deltaTime);
	}
}

void MapGeneratorComponent::Render(sf::RenderTarget& target)
{
	for (auto& map : maps)
	{
		map->Render(target);
	}
}

void MapGeneratorComponent::RenderDeferred(sf::RenderTarget& target)
{
	for (auto& map : maps)
	{
		map->RenderDeferred(target);
	}
}
