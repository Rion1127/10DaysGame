#include "IEnemy.h"
#include "WinAPI.h"

IEnemy::IEnemy()
{
	sprite_ = std::make_unique<Sprite>();
	sprite_->Ini();
	sprite_->SetTexture(TextureManager::GetInstance()->GetTexture("Enemy"));
	Vector2 pos = {
		WinAPI::GetWindowSize().x / 3.5f,
		WinAPI::GetWindowSize().y / 5.f
	};
	sprite_->SetPos(pos);

	// トランスフォーム
	trfm_.Initialize();
	trfm_.pos_ = Vector3(sprite_->GetPos().x, sprite_->GetPos().y, 0.0f);

	// アニメーション用
	hitActor_.Initialize();
}

IEnemy::IEnemy(int32_t health, int32_t attackPower)
{
	sprite_ = std::make_unique<Sprite>();
	sprite_->Ini();
	sprite_->SetTexture(TextureManager::GetInstance()->GetTexture("Enemy"));
	Vector2 pos = {
		WinAPI::GetWindowSize().x / 1.5f,
		WinAPI::GetWindowSize().y / 5.f
	};
	sprite_->SetPos(pos);

	health_ = health;
	isAlive_ = true;
	attackPower_ = attackPower;

	// トランスフォーム
	trfm_.Initialize();
	trfm_.pos_ = Vector3(sprite_->GetPos().x, sprite_->GetPos().y, 0.0f);

	// アニメーション用
	hitActor_.Initialize();
}

void IEnemy::Damage(int32_t health)
{
	health_ -= health;
	if (health_ <= 0) {
		isAlive_ = false;
	}

	// 被弾アニメーション
	//hitActor_.Hit(10.0f, 1.0f);
}
