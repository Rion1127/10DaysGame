#include "EnemyDrawer.h"
#include "YCameraManager.h"

using YGame::EnemyDrawer;

void EnemyDrawer::Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent)
{
	BaseInitialize(trfmStatus, matParent);
	sprite_.SetTexture(TextureManager::GetInstance()->GetTexture("Enemy"));

	hitActor_.Initialize();
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
	animeStatus_.pos_ += hitActor_.ShakePosValue();

	sprite_.SetColor(hitActor_.ColorValue());
}
