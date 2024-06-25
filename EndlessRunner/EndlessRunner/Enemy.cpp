#include "PCH.h"
#include "Enemy.h"

Enemy::Enemy()
{

}

Enemy::~Enemy()
{

}

void Enemy::UpdateAnimation(const float& deltaTime)
{
	animationComponent->Play("IDLE", deltaTime);
}