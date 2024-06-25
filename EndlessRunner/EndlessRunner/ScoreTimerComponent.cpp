#include "PCH.h"
#include "ScoreTimerComponent.h"

ScoreTimerComponent::ScoreTimerComponent()
{

}

ScoreTimerComponent::~ScoreTimerComponent()
{

}

int ScoreTimerComponent::GetScore()
{
	return score;
}

void ScoreTimerComponent::StartTimer()
{
	countTime = true;
}

void ScoreTimerComponent::EndTimer()
{
	countTime = false;
}

bool ScoreTimerComponent::SaveToFile(std::string key, int score)
{
	if (!std::filesystem::exists("Resources/Scores"))
	{
		std::filesystem::create_directories("Resources/Scores");
	}

	std::ofstream out("Resources/Scores/Scores.txt");

	std::string checkString = key + " " + std::to_string(score);

	if (!std::regex_match(checkString, pattern))
	{
		return false;
	}

	if (out)
	{
		std::pair data(key, score);
		scores.push_back(data);

		std::ranges::sort(scores, std::ranges::greater{}, &std::pair<std::string, int>::second);

		for (auto& it : scores)
		{
			out << it.first << " " << it.second<<"\n";
		}

		out.close();
		return true;
	}

	return false;
}

bool ScoreTimerComponent::LoadFromFile()
{
	if (!std::filesystem::exists("Resources/Scores"))
	{
		std::filesystem::create_directories("Resources/Scores");
	}

	std::ifstream in("Resources/Scores/Scores.txt");

	if (in)
	{
		std::string temp = "";
		while (std::getline(in, temp))
        {
			std::smatch match;
            if (std::regex_match(temp, match, pattern))
            {
				std::pair data(match[1], std::stoi(match[2]));
				scores.push_back(data);
            }
			else
			{
				in.close();
				std::filesystem::remove("Resources/Scores/Scores.txt");
				return false;
			}
        }

		in.close();
		return true;
	}

	return false;
}

void ScoreTimerComponent::Update(const float& deltaTime)
{
	if (countTime)
	{
		if (timer <= 0.f)
		{
			score += 1;
			timer = maxTimer;
		}
		else
		{
			timer -= deltaTime;
		}
	}
}
