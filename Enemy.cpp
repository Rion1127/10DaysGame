#include "Enemy.h"

void Enemy::Initialize()
{
	sprite_ = std::make_unique<Sprite>();
	sprite_->Ini();
	sprite_->SetTexture(TextureManager::GetInstance()->GetTexture("Enemy"));
	sprite_->SetPos(Vector2(400, 500));
	sprite_->SetPos(Vector2(400, 500));
}

void Enemy::Update()
{
	sprite_->Update();
}

void Enemy::Draw()
{
	sprite_->Draw();
}