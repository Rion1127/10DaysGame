#include "TitleDrawer.h"
#include "WinAPI.h"
#include "RRandom.h"

using YGame::TitleDrawer;

void TitleDrawer::Initialize()
{
	Vector3 center = Vector3(WinAPI::GetWindowSize().x, WinAPI::GetWindowSize().y, 0.0f) / 2.0f;

	back_.Initialize({ center,{},{1.0f,1.0f,0.0f} }, nullptr);
	logo_.Initialize({ Vector3(248.0f,216.0f,0.0f),{},{1.0f,1.0f,0.0f} }, nullptr);
	for (size_t i = 0; i < clouds_.size(); i++)
	{
		clouds_[i].Initialize({ {}, {}, {1.0f,1.0f,0.0f} }, nullptr, 0);
	}
	
	emitTimer_.Initialize(60 * 15, true);

	for (size_t i = 0; i < 3; i++)
	{
		Vector3 pos = { 0.0f,0.0f,0.0f };
		pos.x = RRandom::RandF(0.0f, WinAPI::GetWindowSize().x);
		pos.y = RRandom::RandF(+64.0f, +128.0f);

		float speed = RRandom::RandF(+0.5f, +1.0f);

		int32_t index = RRandom::Rand(0, 1);

		clouds_[i].EmitAnimation(pos, speed, index);
	}
}

void TitleDrawer::Update()
{
	emitTimer_.Update();
	if (emitTimer_.IsEnd())
	{
		emitTimer_.Reset(true);
		EmitCloud();
	}

	back_.Update();
	logo_.Update();
	for (size_t i = 0; i < clouds_.size(); i++)
	{
		clouds_[i].Update();
	}
}

void TitleDrawer::Draw()
{
	back_.Draw();
	for (size_t i = 0; i < clouds_.size(); i++)
	{
		if (clouds_[i].IsAlive() == false) { continue; }
		clouds_[i].Draw();
	}
	logo_.Draw();
}

void TitleDrawer::EmitCloud()
{
	size_t count = 0;
	for (size_t i = 0; i < clouds_.size(); i++)
	{
		if (clouds_[i].IsAlive()) { continue; }

		Vector3 pos = { -128.0f,0.0f,0.0f };
		pos.y = RRandom::RandF(+64.0f, +128.0f);

		float speed = RRandom::RandF(+0.5f, +1.0f);

		int32_t index = RRandom::Rand(0, 1);

		clouds_[i].EmitAnimation(pos, speed, index);
		
		if (1 <= count++) { return; }
	}
}

void TitleDrawer::CloudDrawer::Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent, const size_t texIndex)
{
	BaseInitialize(trfmStatus, matParent);
	if (texIndex == 0)
	{
		sprite_.SetTexture(TextureManager::GetInstance()->GetTexture("Cloud1"));
	}
	if (texIndex == 1)
	{
		sprite_.SetTexture(TextureManager::GetInstance()->GetTexture("Cloud2"));
	}
	ResetAnimation();
}

void TitleDrawer::CloudDrawer::EmitAnimation(const Vector3& pos, const float speed, const size_t texIndex)
{
	ResetAnimation();
	
	isAlive_ = true;
	trfm_.pos_ = pos;
	speed_ = speed;
	if (texIndex == 0)
	{
		sprite_.SetTexture(TextureManager::GetInstance()->GetTexture("Cloud1"));
	}
	if (texIndex == 1)
	{
		sprite_.SetTexture(TextureManager::GetInstance()->GetTexture("Cloud2"));
	}
}

void TitleDrawer::CloudDrawer::ResetAnimation()
{
	isAlive_ = false;
	speed_ = 0.0f;
}

void TitleDrawer::CloudDrawer::UpdateAnimation()
{
	if (isAlive_ == false) { return; }

	trfm_.pos_.x += speed_;

	if (WinAPI::GetWindowSize().x + 256.0f <= trfm_.pos_.x)
	{
		isAlive_ = false;
	}
}

void TitleDrawer::BackDrawer::Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent)
{
	BaseInitialize(trfmStatus, matParent);
	sprite_.SetTexture(TextureManager::GetInstance()->GetTexture("Title"));
}

void TitleDrawer::TitleLogoDrawer::Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent)
{
	BaseInitialize(trfmStatus, matParent);
	sprite_.SetTexture(TextureManager::GetInstance()->GetTexture("TitleLogo"));
}