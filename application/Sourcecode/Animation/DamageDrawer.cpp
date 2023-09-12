#include "DamageDrawer.h"

using YGame::DamageDrawer;

void DamageDrawer::CreateDigits()
{
	for (size_t i = 0; i < digits_.size(); i++)
	{
		digits_[i] = std::make_unique<DamageDigitDrawer>();
	}
}

void DamageDrawer::Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent, const int32_t number)
{
	NumberDrawer::Initialize(trfmStatus, matParent, number);

	dispTim_.Initialize(30);

	emitTim_.Initialize(4);
	emitCounter_ = 0;

	critical_.Initialize(trfmStatus, matParent);
}

void DamageDrawer::Update(const YTransform::Status& animeStatus)
{
	emitTim_.Update();
	if (emitTim_.IsEnd())
	{
		size_t index = (digits_.size() - 1) - emitCounter_;

		static_cast<DamageDigitDrawer*>(digits_[index].get())->PopAnimation();

		emitCounter_++;
		bool isContinue = (emitCounter_ < digits_.size());
		emitTim_.Reset(isContinue);
		if (isContinue == false)
		{
			dispTim_.Reset(true);
		}
	}

	dispTim_.Update();
	if(dispTim_.IsEnd())
	{
		for (size_t i = 0; i < digits_.size(); i++)
		{
			static_cast<DamageDigitDrawer*>(digits_[i].get())->SetIsDisp(false);
		}
		critical_.SetIsDisp(false);
	}

	NumberDrawer::Update(animeStatus);

	critical_.Update();
}

void DamageDrawer::Draw()
{
	critical_.DrawBack();
	NumberDrawer::Draw();
	critical_.DrawFront();
}

void DamageDrawer::DamageAnimation()
{
	dispTim_.Reset(false);
	
	emitTim_.Reset(true);
	emitCounter_ = 0;

	for (size_t i = 0; i < digits_.size(); i++)
	{
		digits_[i]->ResetAnimation();
		static_cast<DamageDigitDrawer*>(digits_[i].get())->SetIsCritical(false);
	}
	
	critical_.ResetAnimation();
}

void DamageDrawer::CriticalAnimation()
{
	dispTim_.Reset(false);

	emitTim_.Reset(true);
	emitCounter_ = 0;

	for (size_t i = 0; i < digits_.size(); i++)
	{
		digits_[i]->ResetAnimation();
		static_cast<DamageDigitDrawer*>(digits_[i].get())->SetIsCritical(true);
	}

	critical_.ResetAnimation();
	critical_.PopAnimation();
}


void DamageDrawer::DamageDigitDrawer::Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent, const int8_t digit)
{
	DigitDrawer::Initialize(trfmStatus, matParent, digit);

	isDisp_ = false;
	isCritical_ = false;

	popTim_.Initialize(20);
	popHeight_.Initialize({ 0.0f, -128.0f, 0.0f }, 4.0f);
	popScale_.Initialize(-1.0f, 0.0f, 4.0f);
	
	alphaPow_.Initialize(8);
	alphaEas_.Initialize(0.0f, 1.0f, 3.0f);
}

void DamageDrawer::DamageDigitDrawer::ResetAnimation()
{
	isDisp_ = false;

	popTim_.Reset();
	alphaPow_.Reset();
}

void DamageDrawer::DamageDigitDrawer::PopAnimation()
{
	isDisp_ = true;
	
	popTim_.Reset(true);
	alphaPow_.Reset();
}

void DamageDrawer::DamageDigitDrawer::UpdateAnimation()
{
	popTim_.Update();

	animeStatus_.pos_.y += popHeight_.Out(popTim_.Ratio());
	
	float scale = popScale_.Out(popTim_.Ratio());
	animeStatus_.scale_ += Vector3(scale / 10.0f, scale, 0.0f);
	
	alphaPow_.Update(isDisp_);

	float alphaRatio = alphaEas_.InOut(alphaPow_.Ratio());
	if (isCritical_) { sprite_.SetColor(Color(200, 200, 20, 255 * alphaRatio)); }
	else { sprite_.SetColor(Color(200, 20, 20, 255 * alphaRatio)); }
}


void DamageDrawer::CriticalDrawer::CriticalFontDrawer::Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent)
{
	BaseInitialize(trfmStatus, matParent);
	sprite_.SetTexture(TextureManager::GetInstance()->GetTexture("CriticalFont"));
}

void DamageDrawer::CriticalDrawer::CriticalEffectDrawer::Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent)
{
	BaseInitialize(trfmStatus, matParent);
	sprite_.SetTexture(TextureManager::GetInstance()->GetTexture("CriticalEffect"));
}

void DamageDrawer::CriticalDrawer::Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent)
{
	trfm_.Initialize(trfmStatus);
	trfm_.parent_ = matParent;

	font_.Initialize({ {0.0f, +64.0f, 0.0f}, {}, {1.0f,1.0f,0.0f} }, &trfm_.m_);
	effect_.Initialize({ {}, {}, {3.0f,3.0f,0.0f} }, &trfm_.m_);

	isDisp_ = false;

	popTim_.Initialize(40);
	popScale_.Initialize(-trfmStatus.scale_.x, 0.0f, 4.0f);

	alphaPow_.Initialize(8);
	alphaEas_.Initialize(0.0f, 1.0f, 3.0f);
}

void DamageDrawer::CriticalDrawer::ResetAnimation()
{
	isDisp_ = false;

	popTim_.Reset();
	alphaPow_.Reset();
}

void DamageDrawer::CriticalDrawer::PopAnimation()
{
	isDisp_ = true;

	popTim_.Reset(true);
	alphaPow_.Reset();
}

void DamageDrawer::CriticalDrawer::Update()
{
	popTim_.Update();
	
	float scaleVal = popScale_.Out(popTim_.Ratio());
	Vector3 scale = Vector3(scaleVal, scaleVal, 0.0f);

	alphaPow_.Update(isDisp_);

	float alphaRatio = alphaEas_.InOut(alphaPow_.Ratio());
	
	effect_.SetColor(Color(255, 255, 255, 255 * alphaRatio));
	font_.SetColor(Color(255, 255, 255, 255 * alphaRatio));

	trfm_.UpdateMatrix({ {}, {}, scale });
	font_.Update();
	effect_.Update();
}

void DamageDrawer::CriticalDrawer::DrawBack()
{
	effect_.Draw();
}

void DamageDrawer::CriticalDrawer::DrawFront()
{
	font_.Draw();
}
