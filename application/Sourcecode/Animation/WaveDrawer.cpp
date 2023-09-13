#include "WaveDrawer.h"

using YGame::WaveDrawer;

void WaveDrawer::Initialize()
{	
	trfm_.Initialize();
	trfm_.pos_ = { WinAPI::GetWindowSize().x / 2.0f, 24.0f, 0.0f };
	trfm_.scale_ = { 0.5f, 0.5f, 0.0f };

	fontDra_.Initialize({ {-64.0f,0.0f,0.0f }, {}, {1.0f,1.0f,0.0f}}, &trfm_.m_);
	counter_.Initialize({ {+64.0f,0.0f,0.0f }, {}, {0.5f,0.5f,0.0f} }, &trfm_.m_, 1);

	isCount_ = false;
	countPow_.Initialize(40);
	dispTim_.Initialize(20);
	countPos_.Initialize(0.0f, 16.0f, 3.0f);
	countScale_.Initialize(0.0f, 0.25f, 3.0f);
}

void WaveDrawer::GoNextWave()
{
	isCount_ = true;
	dispTim_.Reset();
}

void WaveDrawer::Update()
{
	countPow_.Update(isCount_);
	if (countPow_.IsMax())
	{
		if (dispTim_.IsAct() == false)
		{
			dispTim_.Reset(true);

			int32_t num = counter_.GetNumber() + 1;
			if (1000 <= num) { num = 999; }
			counter_.ChangeAnimation(num);
		}
	}

	dispTim_.Update();
	if (dispTim_.IsEnd())
	{
		isCount_ = false;
		dispTim_.Reset();
	}

	YTransform::Status anime;

	anime.pos_.y += countPos_.InOut(countPow_.Ratio());
	
	float scale = countScale_.InOut(countPow_.Ratio());
	anime.scale_ += {scale, scale, 0.0f};

	trfm_.UpdateMatrix(anime);
	fontDra_.Update();
	counter_.Update();
}

void WaveDrawer::Draw()
{
	fontDra_.Draw();
	counter_.Draw();
}

void WaveDrawer::WaveFontDrawer::Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent)
{
	BaseInitialize(trfmStatus, matParent);
	sprite_.SetTexture(TextureManager::GetInstance()->GetTexture("Wave"));
}
