#include "MinoCounterDrawer.h"
#include "WinAPI.h"

using YGame::MinoCounterDrawer;

void MinoCounterDrawer::Initialize()
{
	elder_ = 0;

	YTransform::Status status = YTransform::Status::Default();
	status.pos_ = { WinAPI::GetWindowSize().x / 2.0f, 650.0f,0.0f};
	status.scale_ = { 0.5f,0.5f,0.0f };

	counter_.Initialize(status, nullptr, 0);
}

void MinoCounterDrawer::Update(const int32_t countNum)
{
	if (elder_ != countNum)
	{
		int32_t num = countNum;
		if (countNum <= 0) { num = 0; }
		counter_.ChangeAnimation(num);
	}

	counter_.Update();

	elder_ = countNum;
}

void MinoCounterDrawer::Draw()
{
	counter_.Draw();
}

void MinoCounterDrawer::CountDrawer::CreateDigits()
{
	for (size_t i = 0; i < digits_.size(); i++)
	{
		digits_[i] = std::make_unique<CountDigitDrawer>();
	}
}

void MinoCounterDrawer::CountDrawer::Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent, const int32_t number)
{
	NumberDrawer::Initialize(trfmStatus, matParent, number);
	elder_ = number;
}

void MinoCounterDrawer::CountDrawer::ChangeAnimation(const int32_t number)
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

void MinoCounterDrawer::CountDrawer::CountDigitDrawer::Initialize(
	const YTransform::Status& trfmStatus, Matrix4* matParent, const int8_t digit)
{
	DigitDrawer::Initialize(trfmStatus, matParent, digit);

	jumpTim_.Initialize(20);
	jumpHeight_.Initialize({ 0.0f, -48.0f, 0.0f }, 4.0f);
}

void MinoCounterDrawer::CountDrawer::CountDigitDrawer::JumpAnimation()
{
	jumpTim_.Reset(true);
}

void MinoCounterDrawer::CountDrawer::CountDigitDrawer::ResetAnimation()
{
	jumpTim_.Reset();
}

void MinoCounterDrawer::CountDrawer::CountDigitDrawer::UpdateAnimation()
{
	jumpTim_.Update();

	animeStatus_.pos_.y += jumpHeight_.Out(jumpTim_.Ratio());
}
