#include "PanelDrawer.h"

using YGame::PanelDrawer;

void PanelDrawer::Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent)
{
	trfm_.Initialize(trfmStatus);
	trfm_.parent_ = matParent;

	blockDra_.Initialize(YTransform::Status::Default(), &trfm_.m_, BlockColorType::None);

	lightDra_.Initialize(YTransform::Status::Default(), &trfm_.m_);

	// アニメーション用
	slimeActor_.Initialize(20, { Vector3(), Vector3(0.4f, 0.4f, 0.4f), Vector3() }, 3.0f);
	rotaTim_.Initialize(40);
	rotaEas_.Initialize(0.0f, 3.141592f * 2.0f, 2.0f);

	isSet_ = false;
	isOpen_ = false;
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
	lightDra_.Update();
}

void PanelDrawer::Draw()
{
	blockDra_.Draw();
	lightDra_.Draw();
}

void PanelDrawer::ResetAnime()
{
	isSet_ = false;
	isOpen_ = false;

	//lightDra_.ResetAnimation();
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

void PanelDrawer::ValidAnimtion()
{
	lightDra_.SetIsAct(false);
}

void PanelDrawer::InvalidAnimtion()
{
	lightDra_.SetIsAct(true);
}

void PanelDrawer::LightDrawer::Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent)
{
	BaseInitialize(trfmStatus, matParent);
	sprite_.SetTexture(TextureManager::GetInstance()->GetTexture("Light"));

	isAct_ = false;
	animePow_.Initialize(40);
	alphaPow_.Initialize(4);

	heightEas_.Initialize(0.0f, -8.0f, 3.0f);
	rotaEas_.Initialize(0.0f, 3.141592f * 6.0f, 3.0f);
	scaleEas_.Initialize(-1.0f, 0.0f, 3.0f);
	alphaEas_.Initialize(1.0, 0.0f, 3.0f);
}

void PanelDrawer::LightDrawer::ResetAnimation()
{
	isAct_ = false;
	animePow_.Reset();
	alphaPow_.Reset();
}

void PanelDrawer::LightDrawer::UpdateAnimation()
{
	animePow_.Update(isAct_);

	//animeStatus_.pos_.y = heightEas_.Out(animePow_.Ratio());
	//animeStatus_.rota_.z = rotaEas_.Out(animePow_.Ratio());
	
	float scale = scaleEas_.Out(animePow_.Ratio());
	animeStatus_.scale_ = Vector3(scale, scale, scale);

	alphaPow_.Update(animePow_.IsZero() || animePow_.IsMax());
	float alphaRatio = alphaEas_.Out(alphaPow_.Ratio());
	sprite_.SetColor(Color(255,255,255,255 * alphaRatio));
}
