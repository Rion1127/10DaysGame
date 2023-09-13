#include "IEnemy.h"
#include "WinAPI.h"

namespace
{
	const size_t kHealthIndex = 0;
	const size_t kAttackIndex = 1;
	const size_t kGuardIndex = 2;
}

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
	drawer_.Initialize(YGame::YTransform::Status::Default(), &trfm_, YGame::EnemyType::Bat);
	hpBar_.Initialize({ {0.0f,96.0f,0.0f},{},{1.0f,1.0f,1.0f} }, &trfm_.m_, health_);
	hpBar_.SetGaugeColor(Color(0, 0, 0, 255), Color(200, 20, 20, 255), Color(20, 200, 20, 255));
	damage_.Initialize({ {0.0f,-32.0f,0.0f},{},{0.5f,0.5f,1.0f} }, &trfm_.m_, 0);

	statusTrfm_.Initialize();
	statusTrfm_.pos_ = Vector3(WinAPI::GetWindowSize().x - 90, 130 - 18, 0);

	statusFrame_.Ini();
	statusFrame_.SetTexture(TextureManager::GetInstance()->GetTexture("EnemyStatusFrame"));
	for (size_t i = 0; i < status_.size(); i++)
	{
		YGame::YTransform::Status status = YGame::YTransform::Status::Default();

		status.pos_ = { statusFrame_.GetPos().x,statusFrame_.GetPos().y - 58.0f,0.0f };
		status.pos_.x += 24.0f;
		status.pos_.y += (i * 36.0f) + 4.0f + 18.0f;

		status.scale_ = { 0.20f,0.20f,1.0f };

		status_[i].Initialize(status, &statusTrfm_.m_);
	}

	status_[kHealthIndex].PowerUpAnimation(health_);
	status_[kAttackIndex].PowerUpAnimation(attackPower_);
	status_[kGuardIndex].PowerUpAnimation(guard_);
}

IEnemy::IEnemy(int32_t health, int32_t attackPower, int32_t guard)
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
	guard_ = guard;

	// トランスフォーム
	trfm_.Initialize();
	trfm_.pos_ = pos;
	trfm_.scale_ = scale;

	// アニメーション用
	drawer_.Initialize(YGame::YTransform::Status::Default(), &trfm_, YGame::EnemyType::Bat);
	hpBar_.Initialize({ {0.0f,96.0f,0.0f},{},{1.0f,1.0f,1.0f} }, &trfm_.m_, health_);
	hpBar_.SetGaugeColor(Color(0, 0, 0, 255), Color(200, 20, 20, 255), Color(20, 200, 20, 255));
	damage_.Initialize({ {0.0f,-32.0f,0.0f},{},{0.5f,0.5f,1.0f} }, &trfm_.m_, 0);

	statusTrfm_.Initialize();
	statusTrfm_.pos_ = Vector3(WinAPI::GetWindowSize().x - 90, 130 - 18, 0);

	statusFrame_.Ini();
	statusFrame_.SetTexture(TextureManager::GetInstance()->GetTexture("EnemyStatusFrame"));
	for (size_t i = 0; i < status_.size(); i++)
	{
		YGame::YTransform::Status status = YGame::YTransform::Status::Default();

		status.pos_ = { statusFrame_.GetPos().x,statusFrame_.GetPos().y - 58.0f,0.0f };
		status.pos_.x += 24.0f;
		status.pos_.y += (i * 36.0f) + 4.0f + 18.0f;

		status.scale_ = { 0.20f,0.20f,1.0f };

		status_[i].Initialize(status, &statusTrfm_.m_);
	}

	status_[kHealthIndex].PowerUpAnimation(health_);
	status_[kAttackIndex].PowerUpAnimation(attackPower_);
	status_[kGuardIndex].PowerUpAnimation(guard_);
}

void IEnemy::AttackAnimation()
{
	drawer_.AttackAnimation();
}

void IEnemy::Damage(int32_t health, const bool isCritical)
{
	health_ -= health;
	if (health_ <= 0) {
		isAlive_ = false;
		drawer_.DeadAnimation();
	}
	
	status_[kHealthIndex].PowerUpAnimation(health_);
	drawer_.HitAnimation();
	
	drawer_.HitAnimation();
	hpBar_.ChangeValueAnimation(health_);
	damage_.SetNumber(health);
	if (isCritical) { damage_.CriticalAnimation(); }
	else { damage_.DamageAnimation(); }
}
