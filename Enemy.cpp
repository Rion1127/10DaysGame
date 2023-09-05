#include "Enemy.h"

Enemy::Enemy(int32_t health) :
	IEnemy(health)
{
}

void Enemy::Initialize() 
{
	
}

void Enemy::Update()
{
	sprite_->Update();
}

void Enemy::Draw()
{
	sprite_->Draw();
}