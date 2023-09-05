#include "IEnemy.h"

IEnemy::IEnemy(int32_t health)
{
	sprite_ = std::make_unique<Sprite>();
	sprite_->Ini();
	sprite_->SetTexture(TextureManager::GetInstance()->GetTexture("Enemy"));
	sprite_->SetPos(Vector2(400, 500));

	health_ = health;
}