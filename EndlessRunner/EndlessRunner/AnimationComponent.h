#pragma once

class AnimationComponent
{
private:
	class Animation
	{
	public:
		sf::Sprite& Sprite;
		sf::Texture& SpriteSheet;
		float AnimationTimer = 60.f;
		float Timer = 0.f;
		bool done = false;
		int Width;
		int Height;
		sf::IntRect StartRect;
		sf::IntRect CurrentRect;
		sf::IntRect EndRect;

		Animation(sf::Sprite& sprite, sf::Texture& spriteSheet, float animationTimer, int startFrameX, int startFrameY, int framesX, int framesY, int width, int height) : Sprite(sprite), SpriteSheet(spriteSheet)
		{
			AnimationTimer = animationTimer;
			Width = width;
			Height = height;
			StartRect = sf::IntRect(startFrameX * Width, startFrameY * Height, Width, Height);
			CurrentRect = StartRect;
			EndRect = sf::IntRect(framesX * Width, framesY * Height, Width, Height);

			Sprite.setTexture(SpriteSheet, true);
			Sprite.setTextureRect(StartRect);
		}

		bool& IsDone()
		{
			return done;
		}

		bool& Play(const float& deltaTime)
		{
			done = false;
			Timer += 100.f * deltaTime;
			if (Timer >= AnimationTimer)
			{
				Timer = 0.f;

				if (CurrentRect != EndRect)
				{
					CurrentRect.left += Width;
				}
				else
				{
					CurrentRect.left = StartRect.left;
					done = true;
				}

				Sprite.setTextureRect(CurrentRect);
			}

			return done;
		}

		void Reset()
		{
			Timer = AnimationTimer;
			CurrentRect = StartRect;
		}
	};

	sf::Sprite& sprite;
	sf::Texture& spriteSheet;
	std::map<std::string, Animation*> animations;
	Animation* lastAnimation = nullptr;
	Animation* priorityAnimation = nullptr;

public:
	AnimationComponent(sf::Sprite& _sprite, sf::Texture& _spriteSheet);
	virtual ~AnimationComponent();

	bool& IsDone(std::string key);

	void AddAnimation(std::string key, float animationTimer, int startFrameX, int startFrameY, int framesX, int framesY, int width, int height);

	bool& Play(std::string key, const float& deltaTime, bool priority = false);
};

