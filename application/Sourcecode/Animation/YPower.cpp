#include "YPower.h"
#include <cmath>

using YMath::YPower;

YPower::YPower(const uint32_t maxPower) : 
	current_(0),
	maxPower_(static_cast<float>(maxPower))
{	
}

void YPower::Initialize(const uint32_t maxPower)
{
	// ���
	SetMaxPower(maxPower);

	// ���Z�b�g
	Reset();
}

void YPower::Reset()
{
	// ������
	current_ = 0;
}

void YPower::Update(const bool isAct)
{
	// ���Z�l
	float spd = 1.0f;

	// ���쒆�Ȃ�
	if (isAct)
	{
		// ���Z (�ő�l�𒴂��Ȃ��悤��)
		current_ = fminf(current_ + spd, maxPower_);
	}
	else
	{
		// ���Z (0.0f�𒴂��Ȃ��悤��)
		current_ = fmaxf(current_ - spd, 0.0f);
	}
}

float YPower::Ratio() const
{
	// 0�Ŋ���Ȃ��悤��
	if (maxPower_ == 0) { return 0.0f; }
	return current_ / maxPower_;
}

void YPower::SetMaxPower(const uint32_t maxPower)
{
	maxPower_ = static_cast<float>(maxPower);
}
