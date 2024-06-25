#pragma once

#include "GameState.h"
#include "EditorState.h"
#include "LeaderBoardState.h"
#include "PlayerDummy.h"
#include "GUI.h"

class MainMenuState : public State
{
private:
	sf::Text titleText;
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	PlayerDummy* playerDummy;

	std::map<std::string, gui::Button*> buttons;

	gui::TextField* textField;

	std::regex adminPassword{"\\!Adm\\*"};
	bool showEditorButton = false;

	void InitTitleText();
	void InitBackground();
	void InitFonts();
	void InitKeybinds();
	void InitButtons();
	void InitGUI();
	void ResestGUI();
	void InitTextures();
	void InitPlayerDummy();

	void RenderDebugPosition(sf::RenderTarget* target);

public:
	MainMenuState(StateData* stateData);
	virtual ~MainMenuState();

	void CheckAdminAccess();
	void UpdateSFMLEvents(sf::Event& event);
	void Update(const float& deltaTime);
	void Render(sf::RenderTarget* target = nullptr);
	void RenderButtons(sf::RenderTarget& target);
	void RenderGUI(sf::RenderTarget& target);
	void UpdateInput(const float& deltaTime);
	void UpdateButtons();
	void UpdateGUI(const float& deltaTime);
};

