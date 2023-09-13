#include "TitleDrawer.h"

using YGame::TitleDrawer;

void TitleDrawer::Initialize()
{
	//back_.Initialize();
	//logo_.Initialize();
	//for (size_t i = 0; i < clouds_.size(); i++)
	//{
	//	clouds_[i].Initialize();
	//}
}

void TitleDrawer::Update()
{
	//back_.Update();
	//logo_.Update();
	for (size_t i = 0; i < clouds_.size(); i++)
	{
		//clouds_[i].Update();
	}
}

void TitleDrawer::Draw()
{
	//back_.Draw();
	for (size_t i = 0; i < clouds_.size(); i++)
	{
		//clouds_[i].Draw();
	}
	//logo_.Draw();
}

void TitleDrawer::CloudDrawer::Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent, const size_t texIndex)
{
	BaseInitialize(trfmStatus, matParent);
	sprite_.SetTexture(TextureManager::GetInstance()->GetTexture("Player"));
}

void TitleDrawer::BackDrawer::Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent)
{
	BaseInitialize(trfmStatus, matParent);
	sprite_.SetTexture(TextureManager::GetInstance()->GetTexture("Player"));
}

void TitleDrawer::TitleLogoDrawer::Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent)
{
	BaseInitialize(trfmStatus, matParent);
	sprite_.SetTexture(TextureManager::GetInstance()->GetTexture("Player"));
}