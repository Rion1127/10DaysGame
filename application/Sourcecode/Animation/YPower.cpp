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
	// 代入
	SetMaxPower(maxPower);

	// リセット
	Reset();
}

void YPower::Reset()
{
	// 初期化
	current_ = 0;
}

void YPower::Update(const bool isAct)
{
	// 加算値
	float spd = 1.0f;

	// 動作中なら
	if (isAct)
	{
		// 加算 (最大値を超えないように)
		current_ = fminf(current_ + spd, maxPower_);
	}
	else
	{
		// 減算 (0.0fを超えないように)
		current_ = fmaxf(current_ - spd, 0.0f);
	}
}

float YPower::Ratio() const
{
	// 0で割らないように
	if (maxPower_ == 0) { return 0.0f; }
	return current_ / maxPower_;
}

void YPower::SetMaxPower(const uint32_t maxPower)
{
	maxPower_ = static_cast<float>(maxPower);
}
