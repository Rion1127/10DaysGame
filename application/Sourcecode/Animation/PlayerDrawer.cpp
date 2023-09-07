#include "PlayerDrawer.h"
#include "YCameraManager.h"

using YGame::PlayerDrawer;

void PlayerDrawer::Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent)
{
	BaseInitialize(trfmStatus, matParent);
	ChangeTexture(TextureType::Idle);
	
	hitActor_.Initialize();

	isIdle_ = true;
	
	isMove_ = false;
	
	moveTim_.Initialize(10);

	moveCount_ = 0;
}

void PlayerDrawer::HitAnimation()
{
	// 被弾アニメーション
	hitActor_.Hit(10.0f, 1.0f);

	float shake = 20.0f;
	float dekey = shake / 10.0f;
	YCameraManager::GetInstance()->ShakeCamera(shake, dekey);
}

void PlayerDrawer::IdleAnimation()
{
	if (isIdle_) { return; }

	ChangeTexture(TextureType::Idle);

	moveTim_.Reset();

	isIdle_ = true;
	
	isMove_ = false;
}

void PlayerDrawer::MoveAnimation()
{
	if (isMove_) { return; }

	ChangeTexture(TextureType::Move);

	moveTim_.Reset(true);
	
	moveCount_ = 0;

	isIdle_ = false;

	isMove_ = true;
}

void PlayerDrawer::ChangeTexture(const TextureType textureType)
{
	if (textureType == TextureType::Idle)
	{
		sprite_.SetTexture(TextureManager::GetInstance()->GetTexture("Player"));
		sprite_.SetTex_LeftTop({});
		sprite_.SetFlipX(false);
		trfm_.scale_ = Vector3(1.0f, 1.0f, 1.0f);
	}
	else if (textureType == TextureType::Move)
	{
		sprite_.SetTexture(TextureManager::GetInstance()->GetTexture("PlayerMove"));
		sprite_.SetTex_LeftTop({});
		sprite_.SetTex_Size({ 128.0f,128.0f });
		sprite_.SetFlipX(true);
		trfm_.scale_ = Vector3(1.0f / 4.0f, 1.0f, 1.0f);
	}
}

void PlayerDrawer::UpdateAnimation()
{
	if (isMove_)
	{
		moveTim_.Update();
		if (moveTim_.IsEnd())
		{
			moveTim_.Reset(true);
			if (4 <= ++moveCount_) { moveCount_ = 0; }

			sprite_.SetTex_LeftTop({ 128.0f * static_cast<float>(moveCount_), 0.0f });
		}
	}

	animeStatus_.pos_ += hitActor_.ShakePosValue();

	sprite_.SetColor(hitActor_.ColorValue());
}
