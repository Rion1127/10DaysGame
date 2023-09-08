#include "TransitionDrawer.h"
#include "WinAPI.h"
#include "RRandom.h"

using YGame::TransitionDrawer;

namespace
{
	const Vector2 kTexSize = { 32.0f,32.0f };
	const float kBlockScale = 1.0f;
}

void TransitionDrawer::Initialize()
{			
	Vector2 winHalf = WinAPI::GetWindowSize() / 2.0f;
	Vector3 pos = { winHalf.x, winHalf.y, 0.0f };
	trfm_.Initialize({ pos, {}, {1.0f,1.0f,1.0f} });


	Vector3 leftTop = 
	{
		static_cast<float>(blocks_[0].size()) * kTexSize.x,
		static_cast<float>(blocks_.size()) * kTexSize.y,
		0.0f
	};
	leftTop *= -0.5f;

	for (size_t y = 0; y < blocks_.size(); y++)
	{
		for (size_t x = 0; x < blocks_[y].size(); x++)
		{
			YTransform::Status status = YTransform::Status::Default();
			
			status.pos_ = Vector3(kTexSize.x * x, kTexSize.y * y, 0.0f) * kBlockScale;
			status.pos_ += leftTop;

			BlockColorType colorType = BlockColorType::None;

			blocks_[y][x].drawer_.Initialize(status, &trfm_.m_, colorType);
		}
	}
}

void TransitionDrawer::Update()
{
	trfm_.UpdateMatrix();
	for (size_t y = 0; y < blocks_.size(); y++)
	{
		for (size_t x = 0; x < blocks_[y].size(); x++)
		{
			Vector3 scale = blocks_[y][x].slime_.WobbleScaleValue(SlimeActor::EaseType::eOut);
			blocks_[y][x].trfm_.UpdateMatrix({ {}, {}, scale });
			blocks_[y][x].drawer_.Update();
		}
	}
}

void TransitionDrawer::SceneChangeAnimation(const uint32_t fallFrame, const uint32_t riseFrame)
{
	for (size_t y = 0; y < blocks_.size(); y++)
	{
		for (size_t x = 0; x < blocks_[y].size(); x++)
		{
			BlockColorType colorType = BlockColorType::None;
			colorType = static_cast<BlockColorType>(RRandom::Rand(3, 9));

			blocks_[y][x].drawer_.ChangeColor(colorType);
		}
	}
}

void TransitionDrawer::Draw()
{
	for (size_t y = 0; y < blocks_.size(); y++)
	{
		for (size_t x = 0; x < blocks_[y].size(); x++)
		{
			blocks_[y][x].drawer_.Draw();
		}
	}
}
