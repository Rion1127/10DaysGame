#include "BaseDrawer.h"

using YGame::BaseDrawer;

void BaseDrawer::Update(const YTransform::Status& status)
{
	if (isResetAnimeStatus_) 
	{
		animeStatus_ = {}; 
	}

	UpdateAnimation();

	YTransform::Status allStatus;
	allStatus.pos_ = animeStatus_.pos_ + status.pos_;
	allStatus.rota_ = animeStatus_.rota_ + status.rota_;
	allStatus.scale_ = animeStatus_.scale_ + status.scale_;

	trfm_.UpdateMatrix(allStatus);

	sprite_.Update(trfm_.m_);
}

void BaseDrawer::Draw()
{
	sprite_.Draw();
}

void BaseDrawer::SetTransform(const YTransform::Status& trfmStatus)
{
	trfm_.Initialize(trfmStatus);
}

void BaseDrawer::BaseInitialize(const YTransform::Status& trfmStatus, Matrix4* matParent)
{
	trfm_.Initialize(trfmStatus);
	trfm_.parent_ = matParent;

	animeStatus_ = {};
	isResetAnimeStatus_ = true;

	sprite_.Ini();

	ResetAnimation();
}
