#pragma once

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "GUI.h"

class EditorState :	public State
{
private:
	sf::View mainView;

	sf::Font font;
	sf::Text cursorText;
	PauseMenu* pauseMenu = nullptr;

	std::map<std::string, gui::Button*> buttons;

	int tileMapsCount = 0;

	int maxTileMapsCount = 20;

	std::vector<gui::Button*> tileMapButtons;

	sf::RectangleShape tileMapBoarder;

	TileMap* currentTileMap = nullptr;

	sf::RectangleShape sidebar;

	sf::IntRect textureRect;
	sf::RectangleShape selectorRect;

	gui::TextureSelector* textureSelector;

	bool collision = false;

	int type = 0;
	int maxType = TileType::TURRET;
	int layer = 0;
	bool addTileLock = false;

	void InitView();
	void InitBackground();
	void InitFonts();
	void InitCursorText();
	void InitKeybinds();
	void InitButtons();
	void InitPauseMenu();
	void InitGUI();
	void InitTextureRect();
	void InitTileMap();

	void RenderCursorText(sf::RenderTarget* target);

	void AddTileMapButton();
	void RemoveTileMapButton();

	void SaveEditorSettings();
	void LoadEditorSettings();

public:
	EditorState(StateData* stateData);
	virtual ~EditorState();

	void UpdateSFMLEvents(sf::Event& event);
	void Update(const float& deltaTime);
	void Render(sf::RenderTarget* target = nullptr);
	void RenderButtons(sf::RenderTarget& target);
	void RenderGUI(sf::RenderTarget& target);
	void UpdateInput(const float& deltaTime);
	void UpdateEditorInput(const float& deltaTime);
	void UpdatePauseMenuButtons();
	void UpdateButtons();
	void UpdateGUI(const float& deltaTime);
};

