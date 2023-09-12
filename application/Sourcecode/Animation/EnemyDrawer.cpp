#include "EnemyDrawer.h"
#include "YCameraManager.h"
#include "Lerp.h"

using YGame::EnemyDrawer;

void EnemyDrawer::Initialize(const YTransform::Status& trfmStatus, YTransform* pTrfm)
{
	BaseInitialize(trfmStatus, &pTrfm->m_);
	sprite_.SetTexture(TextureManager::GetInstance()->GetTexture("Enemy"));
	sprite_.SetTex_LeftTop({});
	sprite_.SetTex_Size({ 128.0f,128.0f });
	trfm_.scale_ = Vector3(1.0f / 6.0f, 1.0f, 1.0f);

	pTrfm_ = pTrfm;

	hitActor_.Initialize();

	moveTim_.Initialize(10, true);
	moveCount_ = 0;
	
	attackEas_.Initialize(
		{
			0.0f, 
			+20.0f, 
			-40.0f, 
			0.0f, 
		}, 
		3.0f);
	attackTim_.Initialize(60);
	isEndAttack_ = false;

	popTim_.Initialize(40, true);
}

void EnemyDrawer::AttackAnimation()
{
	attackTim_.Reset(true);
}

void EnemyDrawer::HitAnimation()
{
	// 被弾アニメーション
	hitActor_.Hit(10.0f, 1.0f);

	float shake = 20.0f;
	float dekey = shake / 10.0f;
	YCameraManager::GetInstance()->ShakeCamera(shake, dekey);
}

void EnemyDrawer::DeadAnimation()
{
	deadActor_.Explosion(pTrfm_->pos_);
}

void EnemyDrawer::UpdateAnimation()
{
	moveTim_.Update();
	if (moveTim_.IsEnd())
	{
		moveTim_.Reset(true);
		if (4 <= ++moveCount_) { moveCount_ = 0; }

		sprite_.SetTex_LeftTop({ 128.0f * static_cast<float>(moveCount_), 0.0f });
	}

	isEndAttack_ = false;
	attackTim_.Update();
	if (attackTim_.IsEnd())
	{
		attackTim_.Reset();
		isEndAttack_ = true;
	}

	popTim_.Update();


	hitActor_.Update();
	animeStatus_.pos_ += hitActor_.ShakePosValue();
	animeStatus_.pos_.x += attackEas_.In(attackTim_.Ratio());

	Color color = hitActor_.ColorValue();
	color.a *= YMath::EaseIn(0.0f, 1.0f, popTim_.Ratio(), 3.0f);
	sprite_.SetColor(color);
}
