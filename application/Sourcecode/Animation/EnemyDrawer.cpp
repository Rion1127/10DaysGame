#include "EnemyDrawer.h"
#include "YCameraManager.h"

using YGame::EnemyDrawer;

void EnemyDrawer::Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent)
{
	BaseInitialize(trfmStatus, matParent);
	sprite_.SetTexture(TextureManager::GetInstance()->GetTexture("Enemy"));
	sprite_.SetTex_LeftTop({});
	sprite_.SetTex_Size({ 128.0f,128.0f });
	trfm_.scale_ = Vector3(1.0f / 6.0f, 1.0f, 1.0f);

	hitActor_.Initialize();

	moveTim_.Initialize(10, true);

	moveCount_ = 0;
}

void EnemyDrawer::HitAnimation()
{
	// 被弾アニメーション
	hitActor_.Hit(10.0f, 1.0f);

	float shake = 20.0f;
	float dekey = shake / 10.0f;
	YCameraManager::GetInstance()->ShakeCamera(shake, dekey);
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

	hitActor_.Update();

	animeStatus_.pos_ += hitActor_.ShakePosValue();

	sprite_.SetColor(hitActor_.ColorValue());
}
