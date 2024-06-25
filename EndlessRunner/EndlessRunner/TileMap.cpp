#include "PCH.h"
#include "TileMap.h"

void TileMap::Clear()
{
	for (int x = 0; x < (int)maxSizeGrid.x; x++)
	{
		for (int y = 0; y < (int)maxSizeGrid.y; y++)
		{
			for (int z = 0; z < layers; z++)
			{
				for (size_t k = 0; k < map[x][y][z].size(); k++)
				{
					delete map[x][y][z][k];
					map[x][y][z][k] = nullptr;
				}
				map[x][y][z].clear();
			}
		}
	}

	while (!deferredRenderList.empty())
	{
		delete deferredRenderList.front();
		deferredRenderList.pop_front();
	}

	for (Enemy* enemy : enemies)
	{
		delete enemy;
	}
}

TileMap::TileMap(int sizex, int sizey, int _offsetX, float _gridSizeF, int layersCount, std::string _tileSheetPath, int index, float _smallOffsetX)
{
	maxSizeGrid.x = sizex;
	maxSizeGrid.y = sizey;
	maxSizeWorld.x = 1920.f;
	maxSizeWorld.y = 1080.f;
	gridSizeF = _gridSizeF;
	gridSizeI = (int)gridSizeF;
	layers = layersCount;
	tileTextureSheetPath = _tileSheetPath;
	offsetX = _offsetX;
	smallOffsetX = _smallOffsetX;

	map.resize(maxSizeGrid.x, std::vector<std::vector<std::vector<Tile*>>>());
	for (int x = 0; x < (int)maxSizeGrid.x; x++)
	{
		for (int y = 0; y < (int)maxSizeGrid.y; y++)
		{
			map[x].resize(maxSizeGrid.y, std::vector<std::vector<Tile*>>());

			for (int z = 0; z < layers; z++)
			{
				map[x][y].resize(layers, std::vector<Tile*>());
			}
		}
	}

	if (!tileTextureSheet.loadFromFile(tileTextureSheetPath))
	{
		throw("TileMap: Could not load TileSheet!");
	}

	collisionBox.setSize(sf::Vector2f(_gridSizeF, _gridSizeF));
	collisionBox.setFillColor(sf::Color(255, 0, 0, 50));
	collisionBox.setOutlineThickness(-1.f);

	collisionBox.setOutlineColor(sf::Color::Red);

	enemyBox.setSize(sf::Vector2f(_gridSizeF, _gridSizeF));
	enemyBox.setFillColor(sf::Color(0, 0, 255, 50));
	enemyBox.setOutlineThickness(-1.f);

	enemyBox.setOutlineColor(sf::Color::Blue);
}

TileMap::~TileMap()
{
	Clear();
}

bool TileMap::TileEmpty(int x, int y, int z)
{
	if (x < (int)maxSizeGrid.x && x >= 0 && y < (int)maxSizeGrid.y && y >= 0 && z < layers && z >= 0)
	{
		return map[x][y][z].empty();
	}
	else
	{
		return true;
	}
}

int TileMap::GetIndex()
{
	return index;
}

void TileMap::SetIndex(int _index)
{
	index = _index;
}

void TileMap::AddTile(int x, int y, int z, sf::IntRect& textureRect, bool& collision, int& type)
{
	if (x < (int)maxSizeGrid.x && x >= 0 &&y < (int)maxSizeGrid.y && y >= 0 && z < layers && z >= 0)
	{
		map[x][y][z].push_back(new Tile(float(x + offsetX), (float)y, gridSizeF, tileTextureSheet, textureRect, collision, type, smallOffsetX));
	}
}

sf::Texture* TileMap::GetTileTextureSheet()
{
	return &tileTextureSheet;
}

int TileMap::GetLayerSize(int x, int y, int layer)
{
	if (x >= 0 && x < (int)map.size())
	{
		if (y >= 0 && y < (int)map[x].size())
		{
			if (layer >= 0 && layer < (int)map[x][y].size())
			{
				return (int)map[x][y][layer].size();
			}
		}
	}

	return -1;
}

sf::Vector2f TileMap::GetPosition(const float& deltaTime)
{
	return map[0][0][0][0]->GetPosition();
}

void TileMap::RemoveTile(int x, int y, int z)
{
	if (x < (int)maxSizeGrid.x && x >= 0 && y < (int)maxSizeGrid.y && y >= 0 && z < layers && z >= 0)
	{
		if (!map[x][y][z].empty())
		{
			delete map[x][y][z][map[x][y][z].size()-1];
			map[x][y][z].pop_back();
		}
	}
}

void TileMap::SaveToFile(std::string fileName)
{
	std::ofstream out(fileName);

	if (out)
	{
		out << index << "\n";
		out << maxSizeGrid.x << " " << maxSizeGrid.y << "\n";
		out << gridSizeI << "\n";
		out << layers << "\n";
		out	<< tileTextureSheetPath << "\n";

		for (int x = 0; x < (int)maxSizeGrid.x; x++)
		{
			for (int y = 0; y < (int)maxSizeGrid.y; y++)
			{
				for (int z = 0; z < layers; z++)
				{
					if (!map[x][y][z].empty())
					{
						for (size_t k = 0; k < map[x][y][z].size(); k++)
						{
							out << x << " " << y << " " << z << " " << map[x][y][z][k]->GetAsString() << "\n";
						}
					}
				}
			}
		}

		out.close();
	}
}

void TileMap::LoadFromFile(std::string fileName, int _index, bool inEditorState)
{
	std::ifstream in(fileName);

	if (in)
	{
		int tempIndex = 0;
		sf::Vector2u size;
		float gridSize = 0.f;
		int layerCount = 1;
		std::string path = "";
		int x = 0;
		int y = 0;
		int z = 0;
		int rectX = 0;
		int rectY = 0;
		bool collision = false;
		int type = 0;

		in >> tempIndex >> size.x >> size.y >> gridSize >> layerCount >> path;

		index = tempIndex;
		gridSizeF = gridSize;
		gridSizeI = (int)gridSize;
		maxSizeGrid.x = size.x;
		maxSizeGrid.y = size.y;
		layers = layerCount;
		tileTextureSheetPath = path;

		Clear();

		map.resize(maxSizeGrid.x, std::vector<std::vector<std::vector<Tile*>>>());
		for (int x = 0; x < (int)maxSizeGrid.x; x++)
		{
			for (int y = 0; y < (int)maxSizeGrid.y; y++)
			{
				map[x].resize(maxSizeGrid.y, std::vector<std::vector<Tile*>>());

				for (int z = 0; z < layers; z++)
				{
					map[x][y].resize(layers, std::vector<Tile*>());
				}
			}
		}

		if (!tileTextureSheet.loadFromFile(tileTextureSheetPath))
		{
			throw("TileMap: Could not load TileSheet!");
		}

		while (in >> x >> y >> z >> rectX >> rectY >> collision >> type)
		{
			map[x][y][z].push_back(new Tile(float(x + offsetX), (float)y, gridSizeF, tileTextureSheet, *(new sf::IntRect(rectX, rectY, gridSizeI, gridSizeI)), collision, type, smallOffsetX));
		}

		if (!inEditorState)
		{
			for (int x = 0; x < (int)maxSizeGrid.x; x++)
			{
				for (int y = 0; y < (int)maxSizeGrid.y; y++)
				{
					for (int z = 0; z < layers; z++)
					{
						if (!map[x][y][z].empty())
						{
							for (size_t k = 0; k < map[x][y][z].size(); k++)
							{
								switch (map[x][y][z][k]->GetType())
								{
								case TileType::SPIKE:
									enemies.push_back(new Spike(map[x][y][z][k]->GetPosition().x, map[x][y][z][k]->GetPosition().y, 1.f, 1.f));
									break;
								case TileType::TURRET:
									enemies.push_back(new Turret(map[x][y][z][k]->GetPosition().x, map[x][y][z][k]->GetPosition().y, 2.f, 2.f));
									break;
								default:
									break;
								}
							}
						}
					}
				}
			}
		}

		in.close();
	}
	else
	{
		Clear();
		index = _index;
	}
}

void TileMap::UpdateCollision(Entity* entity, const float& deltaTime)
{
	layer = 0;

	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 17; y++)
		{
			for (size_t k = 0; k < map[x][y][layer].size(); k++)
			{
				sf::FloatRect entityBounds = entity->GetGlobalBounds();
				sf::FloatRect wallBounds = map[x][y][layer][k]->GetGlobalBounds();
				sf::FloatRect NextWallBounds = map[x][y][layer][k]->GetNextGlobalBounds(deltaTime);
				sf::FloatRect nextPositionBounds = entity->GetNextPositionBounds(deltaTime);

				if (map[x][y][layer][k]->GetCollision() && map[x][y][layer][k]->Intersects(nextPositionBounds, deltaTime))
				{
					if (entityBounds.top < wallBounds.top
						&& entityBounds.top + entityBounds.height < wallBounds.top + wallBounds.height
						&& entityBounds.left < wallBounds.left + wallBounds.width
						&& entityBounds.left + entityBounds.width > wallBounds.left)
					{
						entity->StopVelocityY();
						entity->SetGroundCheck(true);
						entity->SetPosition(entityBounds.left, NextWallBounds.top - entityBounds.height);
					}
					else if (entityBounds.top > wallBounds.top
						&& entityBounds.top + entityBounds.height > wallBounds.top + wallBounds.height
						&& entityBounds.left < wallBounds.left + wallBounds.width
						&& entityBounds.left + entityBounds.width > wallBounds.left)
					{
						entity->StopVelocityY();
						entity->SetPosition(entityBounds.left, NextWallBounds.top + NextWallBounds.height);
					}
					else if (entityBounds.left < wallBounds.left
						&& entityBounds.left + entityBounds.width < wallBounds.left + wallBounds.width
						&& entityBounds.top < wallBounds.top + wallBounds.height
						&& entityBounds.top + entityBounds.height > wallBounds.top)
					{
						entity->StopVelocityX();
						entity->SetPosition(NextWallBounds.left - entityBounds.width, entityBounds.top);
					}
					else if (entityBounds.left > wallBounds.left
						&& entityBounds.left + entityBounds.width > wallBounds.left + wallBounds.width
						&& entityBounds.top < wallBounds.top + wallBounds.height
						&& entityBounds.top + entityBounds.height > wallBounds.top)
					{
						entity->StopVelocityX();
						entity->SetPosition(NextWallBounds.left + NextWallBounds.width, entityBounds.top);
					}
				}
			}		
		}
	}
}

bool TileMap::UpdateEnemyAttacks(Entity* entity, const float& deltaTime)
{
	for (Enemy* enemy : enemies)
	{
		if (enemy->Attack(entity->GetNextPositionBounds(deltaTime)))
		{
			return true;
		}
	}

	return false;
}

void TileMap::Update(const float& deltaTime)
{
	for (auto& x : map)
	{
		for (auto& y : x)
		{
			for (auto& z : y)
			{
				for (auto* k : z)
				{
					if (k != nullptr)
					{
						k->Update(deltaTime);
					}
				}
			}
		}
	}

	for (Enemy* enemy : enemies)
	{
		enemy->Update(deltaTime);
	}
}

void TileMap::Render(sf::RenderTarget& target, bool showCollision)
{
	for (auto& x : map)
	{
		for (auto& y : x)
		{
			for (auto& z : y)
			{
				for (auto* k : z)
				{
					if (k != nullptr)
					{
						if (k->GetType() == TileType::FRONT)
						{
							deferredRenderList.push_back(k);
						}
						else
						{
							k->Render(target);

							if (k->GetCollision() && showCollision)
							{
								collisionBox.setPosition(k->GetPosition());
								target.draw(collisionBox);
							}

							if (showCollision && (k->GetType() == TileType::SPIKE || k->GetType() == TileType::TURRET))
							{
								enemyBox.setPosition(k->GetPosition());
								target.draw(enemyBox);
							}
						}
					}
				}
			}
		}
	}
}

void TileMap::RenderDeferred(sf::RenderTarget& target, bool showCollision)
{
	while (!deferredRenderList.empty())
	{
		deferredRenderList.front()->Render(target);

		if (deferredRenderList.front()->GetCollision() && showCollision)
		{
			collisionBox.setPosition(deferredRenderList.front()->GetPosition());
			target.draw(collisionBox);
		}

		if (showCollision && (deferredRenderList.front()->GetType() == TileType::SPIKE || deferredRenderList.front()->GetType() == TileType::TURRET))
		{
			enemyBox.setPosition(deferredRenderList.front()->GetPosition());
			target.draw(enemyBox);
		}

		deferredRenderList.pop_front();
	}

	for (Enemy* enemy : enemies)
	{
		enemy->Render(target);
	}
}
