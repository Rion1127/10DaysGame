#include "IEnemy.h"
#include "WinAPI.h"

IEnemy::IEnemy()
{
	Vector3 pos = {
		WinAPI::GetWindowSize().x / 2.0f + 256.0f,
		WinAPI::GetWindowSize().y / 6.0f,
		0.0f
	};

	Vector3 scale = { 0.75f,0.75f,0.0f };

	health_ = 0;
	isAlive_ = false;
	attackPower_ = 0;

	// トランスフォーム
	trfm_.Initialize();
	trfm_.pos_ = pos;
	trfm_.scale_ = scale;

	// アニメーション用
	drawer_.Initialize(YGame::YTransform::Status::Default(), &trfm_.m_);
	hpBar_.Initialize({ {0.0f,96.0f,0.0f},{},{1.0f,1.0f,1.0f} }, &trfm_.m_, health_);
	hpBar_.SetGaugeColor(Color(0, 0, 0, 255), Color(200, 20, 20, 255), Color(20, 200, 20, 255));
	damage_.Initialize({ {0.0f,-32.0f,0.0f},{},{0.5f,0.5f,1.0f} }, &trfm_.m_, 0);
}

IEnemy::IEnemy(int32_t health, int32_t attackPower)
{
	Vector3 pos = {
		WinAPI::GetWindowSize().x / 2.0f + 128.0f,
		WinAPI::GetWindowSize().y / 6.0f + 8.0f,
		0.0f
	};

	Vector3 scale = { 0.75f,0.75f,0.0f };

	health_ = health;
	isAlive_ = true;
	attackPower_ = attackPower;

	// トランスフォーム
	trfm_.Initialize();
	trfm_.pos_ = pos;
	trfm_.scale_ = scale;

	// アニメーション用
	drawer_.Initialize(YGame::YTransform::Status::Default(), &trfm_.m_);
	hpBar_.Initialize({ {0.0f,96.0f,0.0f},{},{1.0f,1.0f,1.0f} }, &trfm_.m_, health_);
	hpBar_.SetGaugeColor(Color(0, 0, 0, 255), Color(200, 20, 20, 255), Color(20, 200, 20, 255));
	damage_.Initialize({ {0.0f,-32.0f,0.0f},{},{0.5f,0.5f,1.0f} }, &trfm_.m_, 0);
}

void IEnemy::AttackAnimation()
{
	drawer_.AttackAnimation();
}

void IEnemy::Damage(int32_t health)
{
	health_ -= health;
	if (health_ <= 0) {
		isAlive_ = false;
	}
	
	drawer_.HitAnimation();
	
	drawer_.HitAnimation();
	hpBar_.ChangeValueAnimation(health_);
	damage_.SetNumber(health);
	damage_.DamageAnimation();
}
