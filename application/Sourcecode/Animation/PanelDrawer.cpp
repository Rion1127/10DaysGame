#include "PanelDrawer.h"

using YGame::PanelDrawer;

void PanelDrawer::Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent)
{
	trfm_.Initialize(trfmStatus);
	trfm_.parent_ = matParent;

	blockDra_.Initialize(YTransform::Status::Default(), &trfm_.m_, BlockColorType::None);

	// アニメーション用
	slimeActor_.Initialize(10, { Vector3(), Vector3(0.4f, 0.4f, 0.4f) }, 3.0f);
	rotaTim_.Initialize(40);

	isSet_ = false;
	isOpen_ = false;

	rotaEas_.Initialize(0.0f, 3.141592f * 2.0f, 2.0f);
}

void PanelDrawer::Update()
{
	// アニメーション
	YGame::YTransform::Status animeStatus;

	slimeActor_.Update();
	animeStatus.scale_ += slimeActor_.WobbleScaleValue(YGame::SlimeActor::EaseType::eOut);

	rotaTim_.Update();
	animeStatus.rota_.z += rotaEas_.InOut(rotaTim_.Ratio());

	// 行列更新
	trfm_.UpdateMatrix(animeStatus);

	blockDra_.Update();
}

void PanelDrawer::Draw()
{
	blockDra_.Draw();
}

void PanelDrawer::ResetAnime()
{
	isSet_ = false;
	isOpen_ = false;
}

void PanelDrawer::ChangeColor(const BlockColorType& colorType)
{
	blockDra_.ChangeColor(colorType);
}

void PanelDrawer::SetAnimation()
{
	if (isSet_) { return; }
	slimeActor_.Wobble();
	isSet_ = true;
}

void PanelDrawer::OpenAnimation()
{
	if (isOpen_) { return; }
	slimeActor_.Wobble();
	rotaTim_.Reset(true);
	isOpen_ = true;
}
