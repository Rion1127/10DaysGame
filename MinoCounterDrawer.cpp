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