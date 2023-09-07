#include "IEnemy.h"
#include "WinAPI.h"

IEnemy::IEnemy()
{
	Vector3 pos = {
		WinAPI::GetWindowSize().x / 3.5f,
		WinAPI::GetWindowSize().y / 5.f,
		0.0f
	};

	health_ = 0;
	isAlive_ = false;
	attackPower_ = 0;

	// �g�����X�t�H�[��
	trfm_.Initialize();
	trfm_.pos_ = pos;

	// �A�j���[�V�����p
	drawer_.Initialize(YGame::YTransform::Status::Default(), &trfm_.m_);
}

IEnemy::IEnemy(int32_t health, int32_t attackPower)
{
	Vector3 pos = {
		WinAPI::GetWindowSize().x / 1.5f,
		WinAPI::GetWindowSize().y / 5.f,
		0.0f
	};

	health_ = health;
	isAlive_ = true;
	attackPower_ = attackPower;

	// �g�����X�t�H�[��
	trfm_.Initialize();
	trfm_.pos_ = pos;

	// �A�j���[�V�����p
	drawer_.Initialize(YGame::YTransform::Status::Default(), &trfm_.m_);
}

void IEnemy::Damage(int32_t health)
{
	health_ -= health;
	if (health_ <= 0) {
		isAlive_ = false;
	}
	
	drawer_.HitAnimation();
}
