#include "TransitionDrawer.h"
#include "WinAPI.h"
#include "RRandom.h"
#include "Lerp.h"

using YGame::TransitionDrawer;

namespace
{
	const Vector2 kTexSize = { 32.0f,32.0f };
	const float kBlockScale = 1.0f;
}

void TransitionDrawer::Initialize()
{			
	Vector2 winHalf = WinAPI::GetWindowSize() / 2.0f;
	Vector3 pos = { winHalf.x + 72.0f, winHalf.y, 0.0f };
	trfm_.Initialize({ pos, {}, {3.0f,3.0f,3.0f} });

	Vector3 leftTop = 
	{
		static_cast<float>(blocks_[0].size()) * kTexSize.x + (kTexSize.x / 2.0f * trfm_.scale_.x),
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

			blocks_[y][x].trfm_.Initialize(status);
			blocks_[y][x].trfm_.parent_ = &trfm_.m_;
			blocks_[y][x].drawer_.Initialize(YTransform::Status::Default(), &blocks_[y][x].trfm_.m_, BlockColorType::None);
			blocks_[y][x].slime_.Initialize(0, { -blocks_[y][x].trfm_.scale_ }, 0.0f);
			blocks_[y][x].isExpand_ = false;
			blocks_[y][x].isContract_ = false;
		}
	}
	
	isTransition_ = false;
	
	intervalTim_.Initialize(0);
	loadTim_.Initialize(20);
	loadPow_.Initialize(20);

	loadDra_.Initialize({ {512, 680, 0}, {}, {1.0f,1.0f,0.0f} });

	phase_ = Phase::Fall;
	phaseNum_ = 0;
	phaseCounter_ = 0;

	isChangeMoment_ = false;
}

void TransitionDrawer::Update()
{
	isChangeMoment_ = false;

	intervalTim_.Update();
	
	if (intervalTim_.IsEnd())
	{
		if (phase_ == Phase::Fall)
		{
			FallAnimation();

			intervalTim_.Reset(true);
			phaseCounter_++;
			if (phaseNum_ <= phaseCounter_)
			{
				phase_ = Phase::Load;
				intervalTim_.Reset(false);
				loadTim_.Reset(true);
			}
		}
		else if (phase_ == Phase::Rise)
		{
			RiseAnimation();

			intervalTim_.Reset(true);
			phaseCounter_--;
			if (phaseCounter_ <= 0)
			{
				isTransition_ = false;

				intervalTim_.Initialize(0);
				
				phase_ = Phase::Fall;
				phaseNum_ = 0;
				phaseCounter_ = 0;
			}
		}
	}

	loadTim_.Update();
	loadPow_.Update(loadTim_.IsAct());
	if (loadTim_.IsEnd())
	{
		isChangeMoment_ = true;
		phase_ = Phase::Rise;
		intervalTim_.Reset(true);
		loadTim_.Reset(false);
	}

	trfm_.UpdateMatrix();
	for (size_t y = 0; y < blocks_.size(); y++)
	{
		for (size_t x = 0; x < blocks_[y].size(); x++)
		{
			blocks_[y][x].slime_.Update(blocks_[y][x].isExpand_ || blocks_[y][x].isContract_);
			Vector3 scale = blocks_[y][x].slime_.WobbleScaleValue(SlimeActor::EaseType::eInOut);
			blocks_[y][x].trfm_.UpdateMatrix({ {}, {}, scale });
			blocks_[y][x].drawer_.Update();
		}
	}

	loadDra_.SetColor(Color(255, 255, 255, 255 * YMath::EaseIn(0.0f, 1.0f, loadPow_.Ratio(), 3.0f)));
	loadDra_.Update();
}

void TransitionDrawer::SceneChangeAnimation(const uint32_t frame, const uint32_t phaseNum)
{
	isTransition_ = true;

	intervalTim_.Initialize(frame / phaseNum, true);
	loadTim_.Reset(false);
	
	phaseNum_ = phaseNum;
	phaseCounter_ = 1;

	for (size_t y = 0; y < blocks_.size(); y++)
	{
		for (size_t x = 0; x < blocks_[y].size(); x++)
		{
			BlockColorType colorType = BlockColorType::None;
			colorType = static_cast<BlockColorType>(RRandom::Rand(3, 9));
			//colorType = BlockColorType::Orange;

			blocks_[y][x].drawer_.ChangeColor(colorType);
			blocks_[y][x].slime_.Initialize(0, { -blocks_[y][x].trfm_.scale_ }, 0.0f);
			blocks_[y][x].isExpand_ = false;
			blocks_[y][x].isContract_ = false;
		}
	}

	isChangeMoment_ = false;

	FallAnimation();
}

void TransitionDrawer::FallAnimation()
{
	phase_ = Phase::Fall;

	size_t animeNum = (blocks_.size() * blocks_[0].size()) / phaseNum_;
	size_t animeCounter = 0;
	while (true)
	{
		size_t x = static_cast<size_t>(RRandom::Rand(0, static_cast<int32_t>(blocks_[0].size() - 1)));
		size_t y = static_cast<size_t>(RRandom::Rand(0, static_cast<int32_t>(blocks_.size() - 1)));

		if (blocks_[y][x].isExpand_) { continue; }

		blocks_[y][x].isExpand_ = true;
		blocks_[y][x].isContract_ = false;
		
		blocks_[y][x].slime_.Initialize(
			20, 
			{ 
				-blocks_[y][x].trfm_.scale_,
				Vector3(0.1f, 0.1f, 0.1f),
				Vector3(),
			},
			3.0f);

		animeCounter++;
		if (animeNum <= animeCounter) { break; }
	}
}

void TransitionDrawer::RiseAnimation()
{
	phase_ = Phase::Rise;

	size_t animeNum = (blocks_.size() * blocks_[0].size()) / phaseNum_;
	size_t animeCounter = 0;
	while (true)
	{
		size_t x = static_cast<size_t>(RRandom::Rand(0, static_cast<int32_t>(blocks_[0].size() - 1)));
		size_t y = static_cast<size_t>(RRandom::Rand(0, static_cast<int32_t>(blocks_.size() - 1)));

		if (blocks_[y][x].isContract_) { continue; }

		blocks_[y][x].isContract_ = true;
		blocks_[y][x].isExpand_ = false;
		
		blocks_[y][x].slime_.Initialize(
			20,
			{
				Vector3(),
				Vector3(0.1f, 0.1f, 0.1f),
				-blocks_[y][x].trfm_.scale_,
			},
			3.0f);

		animeCounter++;
		if (animeNum <= animeCounter) { break; }
	}
}

void TransitionDrawer::Draw()
{
	//if (isTransition_ == false) { return; }

	for (size_t y = 0; y < blocks_.size(); y++)
	{
		for (size_t x = 0; x < blocks_[y].size(); x++)
		{
			blocks_[y][x].drawer_.Draw();
		}
	}

	loadDra_.Draw();
}

void TransitionDrawer::LoadDrawer::Initialize(const YTransform::Status& trfmStatus)
{
	BaseInitialize(trfmStatus, nullptr);
	sprite_.SetTexture(TextureManager::GetInstance()->GetTexture("Load"));
}
