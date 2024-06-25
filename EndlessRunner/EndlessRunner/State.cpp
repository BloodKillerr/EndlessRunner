#include "PCH.h"
#include "State.h"

State::State(StateData* _stateData)
{
	stateData = _stateData;
	window = stateData->Window;
	supportedKeys = stateData->SupportedKeys;
	states = stateData->States;
	gridSize = stateData->GridSize;
}

State::~State()
{
	
}

bool State::GetKeyTime()
{
	if (keyTime >= keyTimeMax)
	{
		keyTime = 0.f;
		return true;
	}
	return false;
}

bool& State::GetQuit()
{
	return quit;
}

void State::EndState()
{
	quit = true;
}

void State::PauseState()
{
	paused = true;
}

void State::ResumeState()
{
	paused = false;
}

void State::UpdateMousePositions(sf::View* view)
{
	mousePositionScreen = sf::Mouse::getPosition();
	mousePositionWindow = sf::Mouse::getPosition(*window);

	if (view)
	{
		window->setView(*view);
	}

	mousePositionView = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
	mousePositionGrid = sf::Vector2i((int)mousePositionView.x / (int)gridSize, (int)mousePositionView.y / (int)gridSize);

	window->setView(window->getDefaultView());
}

void State::UpdateKeyTime(const float& deltaTime)
{
	if (keyTime < keyTimeMax)
	{
		keyTime += 100.f * deltaTime;
	}
}
