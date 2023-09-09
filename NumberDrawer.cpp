#include "NumberDrawer.h"

using YGame::NumberDrawer;

static const Vector2 kNumberSize = { 96.0f, 96.0f };

void NumberDrawer::CreateDigits()
{
	for (size_t i = 0; i < digits_.size(); i++)
	{
		digits_[i] = std::make_unique<DigitDrawer>();
	}
}

void NumberDrawer::Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent, const int32_t number)
{
	trfm_.Initialize(trfmStatus);
	trfm_.parent_ = matParent;

	offset_ = {};

	CreateDigits();

	for (size_t i = 0; i < digits_.size(); i++)
	{
		YTransform::Status status = YTransform::Status::Default();

		status.pos_ = { kNumberSize.x * i, 0.0f, 0.0f };

		digits_[i]->Initialize(status, &trfm_.m_, 0);
	}

	SetNumber(number);
}

void NumberDrawer::Update()
{
	trfm_.UpdateMatrix({ offset_ });
	
	for (size_t i = 0; i < digits_.size(); i++)
	{
		digits_[i]->Update();
	}
}

void NumberDrawer::Draw()
{
	for (size_t i = 0; i < digits_.size(); i++)
	{
		digits_[i]->Draw();
	}
}

void NumberDrawer::SetNumber(const int32_t number)
{
	assert(0 <= number_ || number_ < 10 * (digits_.size() + 1));
	number_ = number;

	for (size_t i = 0; i < digits_.size(); i++)
	{
		digits_[i]->SetInvisible(true);
	}

	int32_t num = number;
	size_t digitNum = 0;
	size_t index = digits_.size() - 1;
	offset_ = {};
	while (true)
	{
		digitNum++;
		int32_t digit= num % 10;
		
		digits_[index]->SetDigit(digit);
		digits_[index]->SetInvisible(false);
		
		if (num < 10 || index <= 0) { break; }

		num /= 10;
		index--;
	}

	float numberSizeX = kNumberSize.x * trfm_.scale_.x;
	offset_.x -= numberSizeX * static_cast<float>(digits_.size() - digitNum);
	offset_.x -= (numberSizeX / 2.0f) * static_cast<float>(digitNum - 1);
}
