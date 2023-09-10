#include "HPDrawer.h"

using YGame::HPDrawer;

static const Vector2 kTexSize = { 256.0f,256.0f };

void HPDrawer::Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent, const int32_t maxHp)
{
	trfm_.Initialize(trfmStatus);
	trfm_.parent_ = matParent;

	for (size_t i = 0; i < bars_.size(); i++)
	{
		YTransform::Status status = YTransform::Status::Default();
		
		status.scale_ = { 0.5f,0.1f,0.0f };
		bars_[i].Initialize(status, &trfm_.m_);
	}
	bars_[0].SetColor(Color(  0,   0,   0, 255));
	bars_[1].SetColor(Color(200,  20,  20, 255));
	bars_[2].SetColor(Color( 20, 200,  20, 255));

	number_.Initialize({ {}, {}, {0.25f,0.25f,0.0f} }, &trfm_.m_, maxHp);

	maxHp_ = maxHp;
	hp_ = maxHp;
}

void HPDrawer::Update()
{
	if (hp_ <= 0) { number_.SetNumber(0); }
	else { number_.SetNumber(hp_); }
	
	trfm_.UpdateMatrix();
	for (size_t i = 0; i < bars_.size(); i++)
	{
		bars_[i].Update();
	}
	number_.Update();
}

void HPDrawer::Draw()
{
	for (size_t i = 0; i < bars_.size(); i++)
	{
		bars_[i].Draw();
	}
	number_.Draw();
}

void HPDrawer::ChangeMaxHPAnimation(const int32_t maxHp)
{
	maxHp_ = maxHp;

	bars_[1].ChangeRatioAnimation(HPRatio(), 80);
	bars_[2].ChangeRatioAnimation(HPRatio(), 40);
}

void HPDrawer::ChangeHPAnimation(const int32_t hp)
{
	hp_ = hp;

	bars_[1].ChangeRatioAnimation(HPRatio(), 80);
	bars_[2].ChangeRatioAnimation(HPRatio(), 40);
}

float HPDrawer::HPRatio()
{
	if (maxHp_ <= 0) { return 0; }
	return static_cast<float>(hp_) / static_cast<float>(maxHp_);
}

void HPDrawer::BarDrawer::Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent)
{
	BaseInitialize(trfmStatus, matParent);
	sprite_.SetTexture(TextureManager::GetInstance()->GetTexture("White"));

	changeTim_.Initialize(0);
	changeEas_.Initialize(1.0f, 1.0f, 3.0f);
}

void HPDrawer::BarDrawer::ChangeRatioAnimation(const float ratio, const uint32_t frame)
{
	float start = changeEas_.End();
	changeTim_.Initialize(frame, true);
	changeEas_.Initialize(start, ratio, 3.0f);
}

void HPDrawer::BarDrawer::UpdateAnimation()
{
	changeTim_.Update();

	float ratio = changeEas_.Out(changeTim_.Ratio());
	float scaleX = trfm_.scale_.x * (1.0f - ratio);

	animeStatus_.pos_.x -= scaleX * kTexSize.x / 2.0f;
	animeStatus_.scale_.x -= scaleX;
}
