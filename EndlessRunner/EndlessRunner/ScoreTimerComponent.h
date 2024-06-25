#pragma once
class ScoreTimerComponent
{
private:
	int score = 0;

	bool countTime = false;

	float maxTimer = 1.f;
	float timer = maxTimer;

	std::vector<std::pair<std::string, int>> scores;

	std::regex pattern{"^([a-zA-Z]{1,5}) ([0-9]+)$"};

public:
	ScoreTimerComponent();
	virtual ~ScoreTimerComponent();

	int GetScore();

	void StartTimer();
	void EndTimer();

	bool SaveToFile(std::string key, int score);
	bool LoadFromFile();

	void Update(const float& deltaTime);
};

