#include "CountDrawer.h"

using YGame::CountDrawer;

void CountDrawer::CreateDigits()
{
	for (size_t i = 0; i < digits_.size(); i++)
	{
		digits_[i] = std::make_unique<CountDigitDrawer>();
	}
}

void CountDrawer::Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent, const int32_t number)
{
	NumberDrawer::Initialize(trfmStatus, matParent, number);
	elder_ = number;
}

void CountDrawer::ChangeAnimation(const int32_t number)
{
	if (elder_ == number) { return; }

	SetNumber(number);

	int32_t current = number;
	int32_t elder = elder_;

	for (size_t i = 0; i < digits_.size(); i++)
	{
		if (current % 10 != elder % 10)
		{
			size_t index = digits_.size() - 1 - i;

			digits_[index]->ResetAnimation();
			static_cast<CountDigitDrawer*>(digits_[index].get())->JumpAnimation();
		}

		current /= 10;
		elder /= 10;
	}

	elder_ = number;
}

void CountDrawer::CountDigitDrawer::Initialize(
	const YTransform::Status& trfmStatus, Matrix4* matParent, const int8_t digit)
{
	DigitDrawer::Initialize(trfmStatus, matParent, digit);

	jumpTim_.Initialize(20);
	jumpHeight_.Initialize({ 0.0f, -48.0f, 0.0f }, 4.0f);
}

void CountDrawer::CountDigitDrawer::JumpAnimation()
{
	jumpTim_.Reset(true);
}

void CountDrawer::CountDigitDrawer::ResetAnimation()
{
	jumpTim_.Reset();
}

void CountDrawer::CountDigitDrawer::UpdateAnimation()
{
	jumpTim_.Update();

	animeStatus_.pos_.y += jumpHeight_.Out(jumpTim_.Ratio());
}
