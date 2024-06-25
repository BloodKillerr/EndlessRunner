#include "PCH.h"
#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& _sprite, sf::Texture& _spriteSheet) : sprite(_sprite), spriteSheet(_spriteSheet)
{

}

AnimationComponent::~AnimationComponent()
{
	for (auto& anim : animations)
	{
		delete anim.second;
	}
}

bool& AnimationComponent::IsDone(std::string key)
{
	return animations[key]->IsDone();
}

void AnimationComponent::AddAnimation(std::string key, float animationTimer, int startFrameX, int startFrameY, int framesX, int framesY, int width, int height)
{
	animations[key] = new Animation(sprite, spriteSheet, animationTimer, startFrameX, startFrameY, framesX, framesY, width, height);
}

bool& AnimationComponent::Play(std::string key, const float& deltaTime, bool priority)
{
	if (priorityAnimation)
	{
		if (priorityAnimation == animations[key])
		{
			if (lastAnimation != animations[key])
			{
				if (lastAnimation == nullptr)
				{
					lastAnimation = animations[key];
				}
				else
				{
					lastAnimation->Reset();
					lastAnimation = animations[key];
				}
			}

			if (animations[key]->Play(deltaTime))
			{
				priorityAnimation = nullptr;
			}
		}
	}
	else
	{
		if (priority)
		{
			priorityAnimation = animations[key];
		}

		if (lastAnimation != animations[key])
		{
			if (lastAnimation == nullptr)
			{
				lastAnimation = animations[key];
			}
			else
			{
				lastAnimation->Reset();
				lastAnimation = animations[key];
			}
		}

		animations[key]->Play(deltaTime);
	}

	return animations[key]->IsDone();
}
