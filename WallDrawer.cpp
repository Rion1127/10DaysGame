#include "WallDrawer.h"
#include "WinAPI.h"
#include "Lerp.h"

using YGame::WallDrawer;

namespace 
{
	const size_t kHealthIndex = 0;
	const size_t kAttackIndex = 1;
	const size_t kLuckIndex = 2;
	const size_t kHealIndex = 3;

	const float kNumberScale = 0.2f;
}

void WallDrawer::Initialize()
{
	for (size_t i = 0; i < walls_.size(); i++)
	{
		YTransform::Status wallStatus = YTransform::Status::Default();
		
		Vector2 center = { (WinAPI::GetWindowSize() / 2.0f).x, 464.0f };

		if (i == kHealthIndex)
		{
			wallStatus.pos_ = Vector3(center.x - 160 - 16, center.y, 0);
			wallStatus.rota_.z = 3.141592f * 0.5f;
		}
		if (i == kAttackIndex)
		{
			wallStatus.pos_ = Vector3(center.x + 160 + 16, center.y, 0);
			wallStatus.rota_.z = 3.141592f * 0.5f;
		}
		if (i == kLuckIndex)
		{
			wallStatus.pos_ = Vector3(center.x, center.y - 160 - 16, 0);
			wallStatus.rota_.z = 3.141592f * 0.0f;
		}
		if (i == kHealIndex)
		{
			wallStatus.pos_ = Vector3(center.x, center.y + 160 + 16, 0);
			wallStatus.rota_.z = 3.141592f * 0.0f;
		}

		walls_[i].wall_.Initialize(wallStatus, nullptr);
		walls_[i].wall_.SetColor(Color(100, 100, 100, 255));

		walls_[i].effect_.Initialize({ wallStatus.pos_, {}, {0.75f,0.75f,0.0f} }, nullptr, i);
		walls_[i].effect_.SetColor(Color(100, 100, 100, 255));
		
		walls_[i].counter_.Initialize({ wallStatus.pos_ + Vector3(20,-20,0), {}, {kNumberScale,kNumberScale,0.0f} }, nullptr, 0);
		walls_[i].plusPow_.Initialize(20);
	}
}

void WallDrawer::Update()
{
	for (size_t i = 0; i < walls_.size(); i++)
	{
		int32_t number = walls_[i].counter_.GetNumber();
		bool isPlus = (0 < number);
		
		if (isPlus) 
		{
			float ratio = static_cast<float>(number) / 10.0f;
			float colorVal = 100.0f * ratio;
			walls_[i].wall_.SetColor(Color(155 + colorVal, 155 + colorVal, 20, 255));
			walls_[i].effect_.SetColor(Color(255, 255, 255, 255)); 
		}
		else 
		{
			walls_[i].wall_.SetColor(Color(100, 100, 100, 255));
			walls_[i].effect_.SetColor(Color(100, 100, 100, 255));
		}

		walls_[i].plusPow_.Update(isPlus);
		float scale = YMath::EaseInOut(-kNumberScale, 0.0f, walls_[i].plusPow_.Ratio(), 3.0f);
		float alphaRatio = YMath::EaseInOut(0.0f, 1.0f, walls_[i].plusPow_.Ratio(), 3.0f);

		walls_[i].counter_.SetColor(Color(200, 200, 20, 255 * alphaRatio));

		walls_[i].wall_.Update();
		walls_[i].effect_.Update();
		walls_[i].counter_.Update({ {}, {}, {scale,scale,0.0f} });
	}
}

void WallDrawer::Draw()
{
	for (size_t i = 0; i < walls_.size(); i++)
	{
		walls_[i].wall_.Draw();
		walls_[i].effect_.Draw();
		walls_[i].counter_.Draw();
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
