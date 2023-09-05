#include "IEnemy.h"

IEnemy::IEnemy()
{
	sprite_ = std::make_unique<Sprite>();
	sprite_->Ini();
	sprite_->SetTexture(TextureManager::GetInstance()->GetTexture("Enemy"));
	sprite_->SetPos(Vector2(800, 200));

	// �g�����X�t�H�[��
	trfm_.Initialize();
	trfm_.pos_ = Vector3(sprite_->GetPos().x, sprite_->GetPos().y, 0.0f);

	// �A�j���[�V�����p
	hitActor_.Initialize();
}

IEnemy::IEnemy(int32_t health, int32_t attackPower)
{
	sprite_ = std::make_unique<Sprite>();
	sprite_->Ini();
	sprite_->SetTexture(TextureManager::GetInstance()->GetTexture("Enemy"));
	sprite_->SetPos(Vector2(700, 100));

	health_ = health;
	isAlive_ = true;
	attackPower_ = attackPower;

	// �g�����X�t�H�[��
	trfm_.Initialize();
	trfm_.pos_ = Vector3(sprite_->GetPos().x, sprite_->GetPos().y, 0.0f);

	// �A�j���[�V�����p
	hitActor_.Initialize();
}

void IEnemy::Damage(int32_t health)
{
	health_ -= health;
	if (health_ <= 0) {
		isAlive_ = false;
	}

	// ��e�A�j���[�V����
	//hitActor_.Hit(10.0f, 1.0f);
}
