#include "IEnemy.h"

IEnemy::IEnemy()
{
	sprite_ = std::make_unique<Sprite>();
	sprite_->Ini();
	sprite_->SetTexture(TextureManager::GetInstance()->GetTexture("Enemy"));
	sprite_->SetPos(Vector2(800, 200));
}

IEnemy::IEnemy(int32_t health, int32_t attackPower)
{
	sprite_ = std::make_unique<Sprite>();
	sprite_->Ini();
	sprite_->SetTexture(TextureManager::GetInstance()->GetTexture("Enemy"));
	sprite_->SetPos(Vector2(800, 100));

	health_ = health;
	isAlive_ = true;
	attackPower_ = attackPower;
}

void IEnemy::Damage(int32_t health)
{
	health_ -= health;
	if (health_ <= 0) {
		isAlive_ = false;
	}
}
