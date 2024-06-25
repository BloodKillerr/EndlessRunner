#pragma once

#include "Tile.h"
#include "Entity.h"
#include "Enemy.h"
#include "Spike.h"
#include "Turret.h"

class TileMap
{
private:
	int index = 0;
	float gridSizeF = 64.f;
	int layers = 1;
	int gridSizeI = (int)gridSizeF;
	sf::Vector2u maxSizeGrid;
	sf::Vector2f maxSizeWorld;
	std::vector<std::vector<std::vector<std::vector<Tile*>>>> map;
	std::list<Tile*> deferredRenderList;
	std::string tileTextureSheetPath;
	sf::Texture tileTextureSheet;
	sf::RectangleShape collisionBox;
	sf::RectangleShape enemyBox;

	std::vector<Enemy*> enemies;

	int layer = 0;

	int offsetX = 0;
	float smallOffsetX = 0.f;

	void Clear();

public:
	TileMap(int sizex, int sizey, int _offsetX, float _gridSizeF, int layersCount, std::string _tileSheetPath, int index = 0, float _smallOffsetX = 0.f);
	virtual ~TileMap();

	bool TileEmpty(int x, int y, int z);
	int GetIndex();
	void SetIndex(int _index);
	sf::Texture* GetTileTextureSheet();
	int GetLayerSize(int x, int y, int layer);
	sf::Vector2f GetPosition(const float& deltaTime);

	void AddTile(int x, int y, int z, sf::IntRect& textureRect, bool& collision, int& type);
	void RemoveTile(int x, int y, int z);

	void SaveToFile(std::string fileName);
	void LoadFromFile(std::string fileName, int _index = 0, bool inEditorState = false);

	void UpdateCollision(Entity* entity, const float& deltaTime);
	bool UpdateEnemyAttacks(Entity* entity, const float& deltaTime);

	void Update(const float& deltaTime);
	void Render(sf::RenderTarget& target, bool showCollision = false);
	void RenderDeferred(sf::RenderTarget& target, bool showCollision = false);
};

