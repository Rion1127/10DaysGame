#include "BaseDrawer.h"

using YGame::BaseDrawer;

void BaseDrawer::Update()
{
	if (isResetAnimeStatus_) 
	{
		animeStatus_ = {}; 
	}

	UpdateAnimation();

	trfm_.UpdateMatrix(animeStatus_);

	sprite_.Update(trfm_.m_);
}

void BaseDrawer::Draw()
{
	sprite_.Draw();
}

void BaseDrawer::BaseInitialize(const YTransform::Status& trfmStatus, Matrix4* matParent)
{
	trfm_.Initialize(trfmStatus);
	trfm_.parent_ = matParent;

	animeStatus_ = {};
	isResetAnimeStatus_ = true;

	sprite_.Ini();
}
