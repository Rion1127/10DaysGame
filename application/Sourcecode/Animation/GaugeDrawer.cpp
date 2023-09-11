#include "GaugeDrawer.h"

using YGame::GaugeDrawer;

static const Vector2 kTexSize = { 256.0f,256.0f };

void GaugeDrawer::Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent, const int32_t maxValue)
{
	trfm_.Initialize(trfmStatus);
	trfm_.parent_ = matParent;

	for (size_t i = 0; i < bars_.size(); i++)
	{
		YTransform::Status status = YTransform::Status::Default();
		
		status.scale_ = { 0.5f,0.1f,0.0f };
		if (i == 0) { status.scale_ = { 0.525f,0.125f,0.0f }; }

		bars_[i].Initialize(status, &trfm_.m_);
		bars_[i].SetColor(Color(0, 0, 0, 255));
	}

	counter_.Initialize({ {}, {}, {0.25f,0.25f,0.0f} }, &trfm_.m_, maxValue);

	maxValue_ = maxValue;
	value_ = maxValue;
}

void GaugeDrawer::SetParent(Matrix4* matParent)
{
	trfm_.parent_ = matParent;
}

void GaugeDrawer::SetNumberColor(const Color& color)
{
	counter_.SetColor(color);
}

void GaugeDrawer::SetGaugeColor(const Color& color0, const Color& color1, const Color& color2)
{
	bars_[0].SetColor(color0);
	bars_[1].SetColor(color1);
	bars_[2].SetColor(color2);
}

void GaugeDrawer::Update()
{
	if (value_ <= 0) { counter_.ChangeAnimation(0); }
	else { counter_.ChangeAnimation(value_); }
	
	trfm_.UpdateMatrix();
	for (size_t i = 0; i < bars_.size(); i++)
	{
		bars_[i].Update();
	}
	counter_.Update();
}

void GaugeDrawer::Draw()
{
	for (size_t i = 0; i < bars_.size(); i++)
	{
		bars_[i].Draw();
	}
	counter_.Draw();
}

void GaugeDrawer::ChangeMaxValueAnimation(const int32_t maxHp)
{
	maxValue_ = maxHp;

	bars_[1].ChangeRatioAnimation(ValueRatio(), 80);
	bars_[2].ChangeRatioAnimation(ValueRatio(), 40);
}

void GaugeDrawer::ChangeValueAnimation(const int32_t hp)
{
	value_ = hp;
	if (maxValue_ <= value_)
	{
		ChangeMaxValueAnimation(value_);
		return;
	}

	bars_[1].ChangeRatioAnimation(ValueRatio(), 80);
	bars_[2].ChangeRatioAnimation(ValueRatio(), 40);
}

float GaugeDrawer::ValueRatio()
{
	if (maxValue_ <= 0) { return 0; }
	return static_cast<float>(value_) / static_cast<float>(maxValue_);
}

void GaugeDrawer::BarDrawer::Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent)
{
	BaseInitialize(trfmStatus, matParent);
	sprite_.SetTexture(TextureManager::GetInstance()->GetTexture("White"));

	changeTim_.Initialize(0);
	changeEas_.Initialize(1.0f, 1.0f, 3.0f);
}

void GaugeDrawer::BarDrawer::ChangeRatioAnimation(const float ratio, const uint32_t frame)
{
	float start = changeEas_.End();
	changeTim_.Initialize(frame, true);
	changeEas_.Initialize(start, ratio, 3.0f);
}

void GaugeDrawer::BarDrawer::UpdateAnimation()
{
	changeTim_.Update();

	float ratio = changeEas_.Out(changeTim_.Ratio());
	float scaleX = trfm_.scale_.x * (1.0f - ratio);

	animeStatus_.pos_.x -= scaleX * kTexSize.x / 2.0f;
	animeStatus_.scale_.x -= scaleX;
}
