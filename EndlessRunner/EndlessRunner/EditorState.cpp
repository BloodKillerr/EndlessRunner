#include "PCH.h"
#include "EditorState.h"

void EditorState::InitView()
{
	mainView.setSize(sf::Vector2f((float)stateData->GraphicsSettings->Resolution.width, (float)stateData->GraphicsSettings->Resolution.height));
	mainView.setCenter((float)stateData->GraphicsSettings->Resolution.width / 2.f, (float)stateData->GraphicsSettings->Resolution.height / 2.f);
}

void EditorState::InitBackground()
{
	
}

void EditorState::InitFonts()
{
	if (!font.loadFromFile("Fonts/NewRocker-Regular.ttf"))
	{
		throw("EditorState: Could not load font!");
	}
}

void EditorState::InitCursorText()
{
	cursorText.setFont(font);
	cursorText.setCharacterSize(24);
}

void EditorState::InitKeybinds()
{
	std::ifstream in("Config/editorstate_keybinds.ini");

	if (in.is_open())
	{
		std::string key = "";
		std::string key1 = "";

		while (in >> key >> key1)
		{
			keybinds[key] = supportedKeys->at(key1);
		}
	}

	in.close();
}

void EditorState::InitButtons()
{
	buttons["AddTileMapButton"] = new gui::Button(1773.f, 104.f, 64.f, 64.f, "Add", &font, 32, {235,148,20,255}, {23,52,55,255}, {32,72,77,255}, {43,96,102,255});
	buttons["RemoveTileMapButton"] = new gui::Button(1847.f, 104.f, 64.f, 64.f, "X", &font, 32, { 235,148,20,255 }, { 23,52,55,255 }, { 32,72,77,255 }, { 43,96,102,255 });
}

void EditorState::InitPauseMenu()
{
	sf::VideoMode& videoMode = stateData->GraphicsSettings->Resolution;
	pauseMenu = new PauseMenu(videoMode, font);
	pauseMenu->AddButton("ResumeStateButton", "Resume", gui::calculateTextSize(100, videoMode), gui::percentToPixelsX(10.42f, videoMode), gui::percentToPixelsY(6.94f, videoMode), gui::percentToPixelsY(37.04f, videoMode));
	pauseMenu->AddButton("SaveStateButton", "Save", gui::calculateTextSize(100, videoMode), gui::percentToPixelsX(10.42f, videoMode), gui::percentToPixelsY(6.94f, videoMode), gui::percentToPixelsY(55.56f, videoMode));
	pauseMenu->AddButton("QuitStateButton", "Quit", gui::calculateTextSize(100, videoMode), gui::percentToPixelsX(10.42f, videoMode), gui::percentToPixelsY(6.94f, videoMode), gui::percentToPixelsY(74.07f, videoMode));
}

void EditorState::InitGUI()
{
	InitButtons();

	sidebar.setPosition(1762.f, 0.f);
	sidebar.setSize(sf::Vector2f(158.f, (float)stateData->GraphicsSettings->Resolution.height));
	sidebar.setFillColor(sf::Color(50, 50, 50, 100));
	sidebar.setOutlineColor(sf::Color(200,200,200,150));
	sidebar.setOutlineThickness(1.f);

	selectorRect.setSize(sf::Vector2f(stateData->GridSize, stateData->GridSize));
	selectorRect.setFillColor(sf::Color(255,255,255,100));
	selectorRect.setOutlineThickness(1.f);
	selectorRect.setOutlineColor(sf::Color::Green);
	selectorRect.setTexture(currentTileMap->GetTileTextureSheet());
	selectorRect.setTextureRect(textureRect);

	textureSelector = new gui::TextureSelector(881.f, 220.f, 640.f, 640.f, stateData->GridSize, currentTileMap->GetTileTextureSheet(), font, "TS");

	tileMapBoarder.setFillColor(sf::Color::Transparent);
	tileMapBoarder.setOutlineThickness(1.f);
	tileMapBoarder.setOutlineColor(sf::Color::White);
	tileMapBoarder.setSize(sf::Vector2f(640.f, 1080.f));


}

void EditorState::InitTextureRect()
{
	textureRect = sf::IntRect(0, 0, (int)stateData->GridSize, (int)stateData->GridSize);
}

void EditorState::InitTileMap()
{
	currentTileMap = new TileMap(10, 17, 0, stateData->GridSize, 1, "Resources/GFX/Tiles/TileSheet.png");
}

void EditorState::RenderCursorText(sf::RenderTarget* target)
{
	target->draw(cursorText);
}

void EditorState::AddTileMapButton()
{
	if (tileMapsCount < maxTileMapsCount)
	{
		if (tileMapsCount % 2)
		{
			tileMapButtons.push_back(new gui::Button(1847.f, 188.f + (tileMapsCount / 2 * 84.f), 64.f, 64.f, std::to_string(tileMapsCount), &font, 32, { 235,148,20,255 }, { 23,52,55,255 }, { 32,72,77,255 }, { 43,96,102,255 }));
		}
		else
		{
			tileMapButtons.push_back(new gui::Button(1773.f, 188.f + (tileMapsCount / 2 * 84.f), 64.f, 64.f, std::to_string(tileMapsCount), &font, 32, { 235,148,20,255 }, { 23,52,55,255 }, { 32,72,77,255 }, { 43,96,102,255 }));
		}

		tileMapsCount++;
	}
}

void EditorState::RemoveTileMapButton()
{
	if (tileMapsCount > 1)
	{
		if (currentTileMap->GetIndex() == std::stoi(tileMapButtons.back()->GetText()))
		{
			std::filesystem::remove("Resources/TileMaps/TileMap" + tileMapButtons.back()->GetText() + ".map");
			tileMapButtons.pop_back();
			tileMapsCount--;
			currentTileMap->LoadFromFile("Resources/TileMaps/TileMap" + tileMapButtons.back()->GetText() + ".map", 0, true);
		}
		else
		{
			std::filesystem::remove("Resources/TileMaps/TileMap" + tileMapButtons.back()->GetText() + ".map");
			tileMapButtons.pop_back();
			tileMapsCount--;
		}
	}
}

void EditorState::SaveEditorSettings()
{
	std::ofstream out("Resources/TileMaps/EditorStateSettings.ini");

	if (out)
	{
		out << tileMapsCount;

		out.close();
	}
}

void EditorState::LoadEditorSettings()
{
	std::ifstream in("Resources/TileMaps/EditorStateSettings.ini");

	if (in)
	{
		in >> tileMapsCount;
	}

	for (int i = 1; i < tileMapsCount; i++)
	{
		if (i % 2)
		{
			tileMapButtons.push_back(new gui::Button(1847.f, 188.f + (i / 2 * 84.f), 64.f, 64.f, std::to_string(i), &font, 32, { 235,148,20,255 }, { 23,52,55,255 }, { 32,72,77,255 }, { 43,96,102,255 }));
		}
		else
		{
			tileMapButtons.push_back(new gui::Button(1773.f, 188.f + (i / 2 * 84.f), 64.f, 64.f, std::to_string(i), &font, 32, { 235,148,20,255 }, { 23,52,55,255 }, { 32,72,77,255 }, { 43,96,102,255 }));
		}
	}

	std::string fileToLoad = "Resources/TileMaps/TileMap0.map";
	currentTileMap->LoadFromFile(fileToLoad, 0, true);

	in.close();
}

EditorState::EditorState(StateData* stateData) : State(stateData)
{
	InitView();
	InitBackground();
	InitFonts();
	InitCursorText();
	InitKeybinds();
	InitPauseMenu();
	InitTextureRect();
	InitTileMap();
	InitGUI();
	AddTileMapButton();
	LoadEditorSettings();
}

EditorState::~EditorState()
{
	for (auto it = buttons.begin(); it != buttons.end(); it++)
	{
		delete it->second;
	}

	for (auto &button : tileMapButtons)
	{
		delete button;
	}

	delete pauseMenu;
	delete currentTileMap;
	delete textureSelector;
}

void EditorState::UpdateSFMLEvents(sf::Event& event)
{

}

void EditorState::Update(const float& deltaTime)
{
	UpdateInput(deltaTime);
	UpdateMousePositions(&mainView);
	UpdateKeyTime(deltaTime);

	if (!paused)
	{
		UpdateGUI(deltaTime);
		UpdateEditorInput(deltaTime);
	}
	else
	{
		pauseMenu->Update(mousePositionWindow);
		UpdatePauseMenuButtons();
	}
}

void EditorState::Render(sf::RenderTarget* target)
{
	if (!target)
	{
		target = window;
	}

	target->setView(mainView);
	currentTileMap->Render(*target, true);
	currentTileMap->RenderDeferred(*target, true);

	target->setView(window->getDefaultView());
	RenderGUI(*target);

	if (paused)
	{
		target->setView(window->getDefaultView());
		pauseMenu->Render(*target);
	}
}

void EditorState::RenderButtons(sf::RenderTarget& target)
{
	for (auto& it : buttons)
	{
		it.second->Render(target);
	}

	for (auto& it : tileMapButtons)
	{
		it->Render(target);
	}
}

void EditorState::RenderGUI(sf::RenderTarget& target)
{
	RenderButtons(target);

	if (!textureSelector->GetActive())
	{
		target.setView(mainView);
		target.draw(selectorRect);
	}

	target.setView(window->getDefaultView());
	textureSelector->Render(target);
	target.draw(sidebar);

	target.setView(mainView);
	RenderCursorText(&target);
	target.draw(tileMapBoarder);
}

void EditorState::UpdateInput(const float& deltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds["CLOSE"])) && GetKeyTime())
	{
		if (paused)
		{
			ResumeState();
		}
		else
		{
			PauseState();
		}
	}
}

void EditorState::UpdateEditorInput(const float& deltaTime)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && GetKeyTime())
	{
		if (sidebar.getGlobalBounds().contains(sf::Vector2f(mousePositionWindow)))
		{
			return;
		}

		if (!textureSelector->GetActive())
		{
			if (addTileLock)
			{
				if (currentTileMap->TileEmpty(mousePositionGrid.x, mousePositionGrid.y, 0))
				{
					currentTileMap->AddTile(mousePositionGrid.x, mousePositionGrid.y, 0, textureRect, collision, type);
				}
			}
			else
			{
				currentTileMap->AddTile(mousePositionGrid.x, mousePositionGrid.y, 0, textureRect, collision, type);
			}
			
		}
		else
		{
			textureRect = textureSelector->GetTextureRect();
		}
	}
	else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && GetKeyTime())
	{
		if (sidebar.getGlobalBounds().contains(sf::Vector2f(mousePositionWindow)))
		{
			return;
		}

		if (!textureSelector->GetActive() && !sidebar.getGlobalBounds().contains(sf::Vector2f(mousePositionWindow)))
		{
			currentTileMap->RemoveTile(mousePositionGrid.x, mousePositionGrid.y, 0);
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds["COLLISION"])) && GetKeyTime())
	{
		collision = !collision;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds["TYPE"])) && GetKeyTime())
	{
		if (type == maxType)
		{
			type = 0;
		}
		else
		{
			type++;
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(keybinds["TILELOCK"])) && GetKeyTime())
	{
		addTileLock = !addTileLock;
	}
}

void EditorState::UpdatePauseMenuButtons()
{
	if (pauseMenu->IsButtonPressed("ResumeStateButton"))
	{
		ResumeState();
	}

	if (pauseMenu->IsButtonPressed("SaveStateButton"))
	{
		std::string fileToSave = "Resources/TileMaps/TileMap" + std::to_string(currentTileMap->GetIndex()) + ".map";
		currentTileMap->SaveToFile(fileToSave);
		SaveEditorSettings();
	}

	if (pauseMenu->IsButtonPressed("QuitStateButton"))
	{
		EndState();
	}
}

void EditorState::UpdateButtons()
{
	for (auto& it : buttons)
	{
		it.second->Update(mousePositionWindow);
	}

	for (auto& it : tileMapButtons)
	{
		it->Update(mousePositionWindow);
	}

	if (buttons["AddTileMapButton"]->IsPressed() && GetKeyTime())
	{
		AddTileMapButton();
		SaveEditorSettings();
	}

	if (buttons["RemoveTileMapButton"]->IsPressed() && GetKeyTime())
	{
		RemoveTileMapButton();
		SaveEditorSettings();
	}

	for (auto& it : tileMapButtons)
	{
		if (it->IsPressed() && GetKeyTime())
		{
			if (currentTileMap != nullptr)
			{
				std::string fileToSave = "Resources/TileMaps/TileMap" + std::to_string(currentTileMap->GetIndex()) + ".map";
				currentTileMap->SaveToFile(fileToSave);
			}

			std::string fileToLoad = "Resources/TileMaps/TileMap" + it->GetText() + ".map";
			currentTileMap->LoadFromFile(fileToLoad, std::stoi(it->GetText()), true);

			SaveEditorSettings();
		}
	}
}

void EditorState::UpdateGUI(const float& deltaTime)
{
	UpdateButtons();

	textureSelector->Update(deltaTime, mousePositionWindow);

	if (!textureSelector->GetActive())
	{
		selectorRect.setTextureRect(textureRect);
		selectorRect.setPosition(mousePositionGrid.x * stateData->GridSize, mousePositionGrid.y * stateData->GridSize);
	}

	cursorText.setPosition(mousePositionView.x + 50.f, mousePositionView.y - 50.f);
	std::stringstream ss;
	ss << mousePositionView.x << " " << mousePositionView.y << "\n" << mousePositionGrid.x << " " << mousePositionGrid.y 
		<< "\nCollision: " << collision << "\nType: " << type <<"\nTiles: "
		<< currentTileMap->GetLayerSize(mousePositionGrid.x, mousePositionGrid.y, layer)
		<<"\n TileLock: "<<addTileLock;
	cursorText.setString(ss.str());
}
