#include "WallDrawer.h"

using YGame::WallDrawer;

namespace 
{
	const size_t kHealthIndex = 0;
	const size_t kAttackIndex = 1;
	const size_t kLuckIndex = 2;
	const size_t kHealIndex = 3;
}

void WallDrawer::Initialize()
{
	for (size_t i = 0; i < walls_.size(); i++)
	{
		YTransform::Status wallStatus = YTransform::Status::Default();
		
		if (i == kHealthIndex)
		{
			wallStatus.pos_ = Vector3();
			wallStatus.rota_.z = 3.141592f * 0.0f;
		}
		if (i == kAttackIndex)
		{
			wallStatus.pos_ = Vector3();
			wallStatus.rota_.z = 3.141592f * 0.0f;
		}
		if (i == kLuckIndex)
		{
			wallStatus.pos_ = Vector3();
			wallStatus.rota_.z = 3.141592f * 0.0f;
		}
		if (i == kHealIndex)
		{
			wallStatus.pos_ = Vector3();
			wallStatus.rota_.z = 3.141592f * 0.0f;

		}

		walls_[i].wall_.Initialize(wallStatus, nullptr);
		walls_[i].effect_.Initialize({ wallStatus.pos_, {}, {1.0f,1.0f,0.0f} }, nullptr, i);
		walls_[i].counter_.Initialize({ wallStatus.pos_, {}, {1.0f,1.0f,0.0f} }, nullptr, 10);
	}
}

void WallDrawer::Update()
{
	for (size_t i = 0; i < walls_.size(); i++)
	{
		walls_[i].wall_.Update();
		walls_[i].effect_.Update();
		walls_[i].counter_.Update();
	}
}

void WallDrawer::Draw()
{
	for (size_t i = 0; i < walls_.size(); i++)
	{
		walls_[i].wall_.Draw();
		walls_[i].effect_.Draw();
		//walls_[i].counter_.Draw();
	}
}

void WallDrawer::ChangePlusHealth(const int32_t plusNum)
{
	int32_t num = plusNum;
	if (plusNum <= 0) { num = 0; }
	walls_[kHealthIndex].counter_.ChangeAnimation(num);
}

void WallDrawer::ChangePlusAttack(const int32_t plusNum)
{
	int32_t num = plusNum;
	if (plusNum <= 0) { num = 0; }
	walls_[kAttackIndex].counter_.ChangeAnimation(num);
}

void WallDrawer::ChangePlusLuck(const int32_t plusNum)
{
	int32_t num = plusNum;
	if (plusNum <= 0) { num = 0; }
	walls_[kLuckIndex].counter_.ChangeAnimation(num);
}

void WallDrawer::ChangePlusHeal(const int32_t plusNum)
{
	int32_t num = plusNum;
	if (plusNum <= 0) { num = 0; }
	walls_[kHealIndex].counter_.ChangeAnimation(num);
}


void WallDrawer::WallPanelDrawer::Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent)
{
	BaseInitialize(trfmStatus, matParent);
	sprite_.SetTexture(TextureManager::GetInstance()->GetTexture("Wall"));
}

void WallDrawer::EffectFontDrawer::Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent, const size_t index)
{
	BaseInitialize(trfmStatus, matParent);
	sprite_.SetTexture(TextureManager::GetInstance()->GetTexture("Effect"));

	trfm_.scale_.x /= 4.0f;

	const float kSize = 64.0f;
	sprite_.SetTex_LeftTop(Vector2(kSize * index, 0.0f));
	sprite_.SetTex_Size(Vector2(kSize, kSize));
}
