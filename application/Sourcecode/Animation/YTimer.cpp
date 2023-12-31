#include "YTimer.h"
#include <cmath>

using YMath::YTimer;

YTimer::YTimer(const uint32_t endFrame, const bool isAct) :
	current_(0),
	endFrame_(endFrame),
	isAct_(isAct)
{
}

void YTimer::Initialize(const uint32_t endFrame, const bool isAct)
{
	// 代入
	SetEndFrame(endFrame);

	// リセット
	Reset(isAct);
}

void YTimer::Reset(const bool isAct)
{
	// 初期化
	current_ = 0;
	isAct_ = isAct;
}

void YTimer::Update(const float passRate)
{
	// 動作中のみ通る
	if (isAct_ == false) { return; }

	// 加算値
	float spd = 1.0f * passRate;

	// 加算
	current_ += spd;
	
	// 時間になったら
	if (current_ >= static_cast<float>(endFrame_))
	{
		// 終了処理
		current_ = static_cast<float>(endFrame_);
		isAct_ = false;
	}
}

float YTimer::Ratio() const
{
	// 0で割らないように
	if (endFrame_ == 0) { return 1.0f; }
	return current_ / static_cast<float>(endFrame_);
}