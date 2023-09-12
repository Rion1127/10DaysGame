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
	}

	NumberDrawer::Update(animeStatus);
}

void DamageDrawer::DamageAnimation()
{
	dispTim_.Reset(false);
	
	emitTim_.Reset(true);
	emitCounter_ = 0;

	for (size_t i = 0; i < digits_.size(); i++)
	{
		digits_[i]->ResetAnimation();
	}
}

void DamageDrawer::DamageDigitDrawer::Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent, const int8_t digit)
{
	DigitDrawer::Initialize(trfmStatus, matParent, digit);

	popTim_.Initialize(20);
	popHeight_.Initialize({ 0.0f, -128.0f, 0.0f }, 4.0f);
	popScale_.Initialize(-1.0f, 0.0f, 4.0f);
	
	alphaPow_.Initialize(8);
	alphaEas_.Initialize(0.0f, 1.0f, 3.0f);
}

void DamageDrawer::DamageDigitDrawer::PopAnimation()
{
	isDisp_ = true;
	
	popTim_.Reset(true);
	alphaPow_.Reset();
}

void DamageDrawer::DamageDigitDrawer::ResetAnimation()
{
	isDisp_ = false;

	popTim_.Reset();
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
	sprite_.SetColor(Color(200, 20, 20, 255 * alphaRatio));
}
