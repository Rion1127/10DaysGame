#include "NextMinoDrawer.h"
#include "Lerp.h"

using YGame::NextMinoDrawer;
using YGame::YTransform;

namespace
{
	const float kScale1 = 0.75f;
	const float kScale2 = 0.5f;
	const float kHeightOffset = 85.0f;
}

void NextMinoDrawer::Initialize()
{
	
	for (size_t i = 0; i < nexts_.size(); i++)
	{
		YTransform::Status status = YTransform::Status::Default();

		if (i <= 1)
		{
			status.pos_ =
			{
				620.0f,
				340.0f,
				0.0f
			};
			status.scale_ *= kScale1;
		}
		else if (i < nexts_.size() - 1)
		{
			status.pos_ =
			{
				620.0f,
				276.0f + kHeightOffset * static_cast<float>(i),
				0.0f
			};
			status.scale_ *= kScale2;
		}
		else
		{
			status.pos_ =
			{
				620.0f,
				276.0f + kHeightOffset * static_cast<float>(i - 1),
				0.0f
			};
			status.scale_ *= kScale2;
		}

		nexts_[i].Initialize(status, nullptr);
	}

	nextDra_.Initialize({ {620.0f,270.0f,0.0f},{},{0.5f,0.5f,0.0f} }, nullptr);

	isReset_ = false;
	resetTimer_.Initialize(40);

	isAdvence_ = false;
	isRetreat_ = false;
	riseTimer_.Initialize(30);

	lock_.lock_.Initialize({ {0.0f,-24.0f,0.0f}, {}, {0.75f,0.75f,0.0f} }, nullptr);
	lock_.block_.Initialize({ {-60.0f,24.0f,0.0f}, {}, {1.2f,1.2f,0.0f} }, nullptr, BlockColorType::Blue);
	lock_.gauge_.Initialize({ {+8.0f,24.0f,0.0f}, {}, {1.0f,1.0f,0.0f} }, nullptr, 0);
	lock_.gauge_.SetNumberColor(Color(255, 255, 255, 255));
	lock_.gauge_.SetGaugeColor(Color(0, 0, 0, 255), Color(20, 200, 200, 255), Color(200, 200, 20, 255));

	isUnlock_ = false;
	unlockPower_.Initialize(40);
	unlockHeightEas_.Initialize(0.0f, 64.0f, 3.0f);
	unlockRotaEas_.Initialize(0.0f, 3.141592f * 0.25f, 3.0f);

}

void NextMinoDrawer::Update(const int32_t minoCount)
{
	riseTimer_.Update();
	if (riseTimer_.IsEnd())
	{
		riseTimer_.Reset(false);
		isAdvence_ = false;
		isRetreat_ = false;

		ChangeNextMino();
	}

	resetTimer_.Update();
	if (0.5f == resetTimer_.Ratio())
	{
		isUnlock_ = false;
		lock_.block_.ChangeColor(BlockColorType::Blue);
		lock_.gauge_.SetNumberColor(Color(255, 255, 255, 255));
		lock_.gauge_.SetGaugeColor(Color(0, 0, 0, 255), Color(20, 200, 200, 255), Color(200, 200, 20, 255));

		for (size_t i = 0; i < nexts_.size(); i++)
		{
			nexts_[i].SetIsExist(true);
		}

		ChangeNextMino();
	}
	if (resetTimer_.IsEnd())
	{
		isReset_ = false;
		resetTimer_.Reset(false);
	}

	for (size_t i = 0; i < nexts_.size(); i++)
	{
		YTransform::Status anime = AnimeStatus(i);
		if (i == nexts_.size() - 1) { anime = {}; }
		nexts_[i].Update(anime);
	}

	unlockPower_.Update(isUnlock_);

	YTransform::Status anime = {};
	anime.pos_.y = unlockHeightEas_.In(unlockPower_.Ratio());
	anime.rota_.z = unlockRotaEas_.In(unlockPower_.Ratio());

	float alpha = YMath::EaseIn(255.0f, 0.0f, unlockPower_.Ratio(), 3.0f);
	lock_.lock_.SetColor(Color(255, 255, 255, alpha));

	lock_.lock_.Update(anime);
	lock_.block_.Update();
	lock_.gauge_.ChangeValueAnimation(minoCount);
	lock_.gauge_.Update();

	nextDra_.Update();
}

void NextMinoDrawer::Draw()
{
	nexts_[0].Draw();
	nexts_[5].Draw();
	nexts_[1].Draw();
	nexts_[2].Draw();
	nexts_[4].Draw();
	nexts_[3].Draw();

	nextDra_.Draw();
}

void NextMinoDrawer::RedrawAnimation(const std::vector<MinoType>& minos)
{
	minos_ = minos;
	if (isReset_)
	{
		ChangeNextMino();
		isReset_ = false;
		resetTimer_.Reset(false);
		return;
	}

	isReset_ = true;
	resetTimer_.Reset(true);

	for (size_t i = 0; i < nexts_.size(); i++)
	{
		nexts_[i].SetIsExist(false);
	}

	isAdvence_ = false;
	isRetreat_ = false;
	riseTimer_.Reset(false);

}

void NextMinoDrawer::UnlockAnimiation()
{
	isUnlock_ = true;
	lock_.block_.ChangeColor(BlockColorType::None);
	lock_.gauge_.SetNumberColor(Color(255, 255, 255, 0));
	lock_.gauge_.SetGaugeColor(Color(0, 0, 0, 0), Color(20, 200, 200, 0), Color(200, 200, 20, 0));
}

void NextMinoDrawer::AdvanceAnimation(const std::vector<MinoType>& minos)
{
	minos_ = minos;
	if (isAdvence_)
	{
		ChangeNextMino();
		isAdvence_ = false;
		riseTimer_.Reset(false);
		return;
	}

	isAdvence_ = true;
	riseTimer_.Reset(true);
}

void NextMinoDrawer::RetreatAnimation(const std::vector<MinoType>& minos)
{
	minos_ = minos;
	if (isRetreat_)
	{
		ChangeNextMino();
		isRetreat_ = false;
		riseTimer_.Reset(false);
		return;
	}

	isRetreat_ = true;
	riseTimer_.Reset(true);

	isUnlock_ = false;
	lock_.block_.ChangeColor(BlockColorType::Blue);
	lock_.gauge_.SetNumberColor(Color(255, 255, 255, 255));
	lock_.gauge_.SetGaugeColor(Color(0, 0, 0, 255), Color(20, 200, 200, 255), Color(200, 200, 20, 255));
}

YTransform::Status NextMinoDrawer::AnimeStatus(const size_t index)
{
	YTransform::Status anime;

	Vector3 scale = Vector3(kScale1, kScale1, 0.0f) - Vector3(kScale2, kScale2, 0.0f);


	if (isAdvence_)
	{
		if (index == 0 || index == 1)
		{
			return {};
		}
		else if (index == 2)
		{
			anime.pos_.y += YMath::EaseOut(0.0f, -kHeightOffset * 1.25f, riseTimer_.Ratio(), 3.0f);
			anime.scale_ += YMath::EaseOut({}, scale, riseTimer_.Ratio(), 3.0f);
		}
		else
		{
			anime.pos_.y += YMath::EaseOut(0.0f, -kHeightOffset, riseTimer_.Ratio(), 3.0f);
		}
	}
	else if (isRetreat_)
	{
		if (index == 0 || 4 <= index)
		{
			return {};
		}
		else if (index == 1)
		{
			anime.pos_.y += YMath::EaseOut(0.0f, +kHeightOffset * 1.25f, riseTimer_.Ratio(), 3.0f);
			anime.scale_ += YMath::EaseOut({}, -scale, riseTimer_.Ratio(), 3.0f);
		}
		else
		{
			anime.pos_.y += YMath::EaseOut(0.0f, +kHeightOffset, riseTimer_.Ratio(), 3.0f);
		}
	}

	return anime;
}

void NextMinoDrawer::ChangeNextMino()
{
	bool isEnd = false;
	for (size_t i = 0; i < nexts_.size(); i++)
	{
		if(minos_.size() <= i) 
		{
			if(isEnd == false)
			{
				nexts_[i].ChangeRock(&lock_);
				isEnd = true;
			}
			else
			{
				nexts_[i].ChangeVoid();
			}
			continue;
		}
		
		nexts_[i].ChangeMino(minos_[i]);
	}
}

void NextMinoDrawer::FrameDrawer::Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent)
{
	BaseInitialize(trfmStatus, matParent);
	sprite_.SetTexture(TextureManager::GetInstance()->GetTexture("Frame"));
}

void NextMinoDrawer::LockDrawer::Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent)
{
	BaseInitialize(trfmStatus, matParent);
	sprite_.SetTexture(TextureManager::GetInstance()->GetTexture("Lock"));
}

void NextMinoDrawer::NextDrawer::Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent)
{
	BaseInitialize(trfmStatus, matParent);
	sprite_.SetTexture(TextureManager::GetInstance()->GetTexture("Next"));
}

void NextMinoDrawer::NextFrameDrawer::Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent)
{
	trfm_.Initialize(trfmStatus);
	trfm_.parent_ = matParent;

	for (size_t i = 0; i < drawers_.size(); i++)
	{
		drawers_[i].Initialize({ {}, {}, {1.0f,1.0f,0.0f} }, &trfm_.m_, BlockColorType::Cyan);
	}
	frame_.Initialize({ {}, {}, {1.5f,1.5f,0.0f} }, &trfm_.m_);

	pLock_ = nullptr;

	isExist_ = false;
	existPow_.Initialize(20);
	existScaleEas_.Initialize(-trfmStatus.scale_, {}, 3.0f);
}

void NextMinoDrawer::NextFrameDrawer::Update(const YTransform::Status& animeStatus)
{
	existPow_.Update(isExist_);

	YTransform::Status anime = animeStatus;

	if (isExist_ == false) { anime.scale_ = {}; }
	anime.scale_ += existScaleEas_.InOut(existPow_.Ratio());

	trfm_.UpdateMatrix(anime);
	frame_.Update();
	for (size_t i = 0; i < drawers_.size(); i++)
	{
		drawers_[i].Update();
	}
}

void NextMinoDrawer::NextFrameDrawer::Draw()
{
	frame_.Draw();
	for (size_t i = 0; i < drawers_.size(); i++)
	{
		drawers_[i].Draw();
	}

	if (pLock_)
	{
		pLock_->lock_.Draw(); 
		pLock_->gauge_.Draw(); 
		pLock_->block_.Draw();
	}
}

void NextMinoDrawer::NextFrameDrawer::ResetAnimation()
{
	isExist_ = true;
	existPow_.Reset();
}

void NextMinoDrawer::NextFrameDrawer::ChangeMino(const MinoType type)
{	
	for (size_t i = 0; i < drawers_.size(); i++)
	{
		drawers_[i].ChangeColor(BlockColorType::Cyan);
	}

	// パネル位置変更
	std::vector<std::vector<uint32_t>> panel = MinoList::GetMinoList(type).panel_;
	size_t dIndex = 0;

	Vector3 offset;

	if (type == MinoType::Omino) { offset = { -16.0f,-16.0f,0.0f }; }
	if (type == MinoType::Tmino) { offset = { -32.0f,-16.0f,0.0f }; }
	if (type == MinoType::Smino) { offset = { -32.0f,-16.0f,0.0f }; }
	if (type == MinoType::Zmino) { offset = { -32.0f,-16.0f,0.0f }; }
	if (type == MinoType::Imino) { offset = {   0.0f,-48.0f,0.0f }; }
	if (type == MinoType::Lmino) { offset = { -32.0f,-16.0f,0.0f }; }
	if (type == MinoType::Jmino) { offset = { -32.0f,-16.0f,0.0f }; }

	for (size_t i = 0; i < panel.size(); i++)
	{
		for (size_t j = 0; j < panel[i].size(); j++)
		{
			if (panel[i][j] != 1) { continue; }

			YTransform::Status status = YTransform::Status::Default();

			status.pos_ = { 32.0f * j, 32.0f * i, 0.0f };
			status.pos_ += offset;

			drawers_[dIndex].SetTransform(status);

			dIndex++;
		}
	}
	frame_.SetColor(Color(255, 255, 255, 255));

	if (pLock_) { pLock_ = nullptr; }
}

void NextMinoDrawer::NextFrameDrawer::ChangeVoid()
{
	for (size_t i = 0; i < drawers_.size(); i++)
	{
		drawers_[i].ChangeColor(BlockColorType::None);
	}
	frame_.SetColor(Color(0, 0, 0, 0));

	if (pLock_) { pLock_ = nullptr; }
}

void NextMinoDrawer::NextFrameDrawer::ChangeRock(Lock* pLock)
{
	for (size_t i = 0; i < drawers_.size(); i++)
	{
		drawers_[i].ChangeColor(BlockColorType::None);
	}
	frame_.SetColor(Color(150, 150, 150, 255));

	pLock_ = pLock;
	pLock_->lock_.SetParent(&trfm_.m_);
	pLock_->block_.SetParent(&trfm_.m_);
	pLock_->gauge_.SetParent(&trfm_.m_);
}

