#include "SwordDrawer.h"
#include "Lerp.h"
#include "YCameraManager.h"
#include "RRandom.h"

using YGame::SwordDrawer;

static const float kPI = 3.141592f;

void SwordDrawer::Initialize(const size_t maxXSize, const size_t maxYSize, Matrix4* matParent)
{
	// 親トランスフォーム
	trfm_.Initialize();
	trfm_.pos_ = Vector3(+64.0f, 0.0f, 0.0f);
	trfm_.parent_ = matParent;

	// ハンドル
	handle_.Initialize(
		{
			Vector3(0.0f, -64.0f, 0.0f),
			{},
			Vector3(0.25f, 1.0f, 0.0f)
		}, &trfm_.m_);

	// パネル縦横分生成
	for (size_t y = 0; y < maxYSize; y++)
	{
		blades_.emplace_back();
		for (size_t x = 0; x < maxXSize; x++)
		{
			blades_[y].emplace_back();
			
			blades_[y][x].Initialize({}, &trfm_.m_);
		}
	}

	// スライムアニメーション
	slime_.Initialize(
		30, 
		{
			{-1.0f, -1.0f, -1.0f},
			{+0.1f, +0.1f, +0.1f},
			{+0.0f, +0.0f, +0.0f},
		},
		5.0f);

	// アニメーション
	rotaEas_.Initialize(0.0f, kPI / 1.5f, 3.5f);
	rotaTim_.Initialize(20);

	alphaPow_.Initialize(10);

	panelCounter_ = 0.0f;

	breakTim_.Initialize(40);

	step_ = AttackStep::None;
}

void SwordDrawer::AttackAnimation(const std::vector<std::vector<int32_t>>& panelIndices)
{
	panelCounter_ = 0.0f;

	static const float kPanelSize = 32.0f;
	static const float kPanelScale = 0.5f;
	
	size_t xSize = panelIndices.size(), ySize = panelIndices[0].size();

	for (size_t i = 0; i < panelIndices.size(); i++)
	{
		for (size_t j = 0; j < panelIndices[i].size(); j++)
		{
			if (panelIndices[i][j] == 2)
			{
				panelCounter_ += 1.0f;
			}

			Vector3 leftTop = -Vector3(kPanelSize * xSize, kPanelSize * ySize, 0.0f) * kPanelScale / 2.0f;
			leftTop -= Vector3(0.0f, kPanelSize * ySize, 0.0f) * kPanelScale / 2.0f;
			leftTop -= Vector3(0.0f, 64.0f, 0.0f);

			YTransform::Status status;
			status.pos_ = Vector3(kPanelSize * i, kPanelSize * j, 0) * kPanelScale + leftTop;
			status.scale_ = Vector3(kPanelScale, kPanelScale, 0);

			blades_[i][j].InitializeAnime(panelIndices[i][j], status);	
		}
	}

	slime_.Wobble();

	rotaTim_.Reset();

	alphaPow_.Reset();

	breakTim_.Reset();

	// 生成
	step_ = AttackStep::Forge;
}

void SwordDrawer::UpdateAttackAnimation(YGame::YTransform::Status& animeStatus)
{
	slime_.Update();

	rotaTim_.Update();

	breakTim_.Update();

	if (slime_.IsAct())
	{
		animeStatus.scale_ +=
			slime_.WobbleScaleValue(YGame::SlimeActor::EaseType::eOut);
	}

	animeStatus.rota_.z +=
		rotaEas_.In(rotaTim_.Ratio());

	// 生成終了
	if (slime_.IsAct() == false && step_ == AttackStep::Forge)
	{
		rotaTim_.Reset(true);

		// 振り下ろす
		step_ = AttackStep::Slash;
	}

	// 振り下ろす終了
	if (rotaTim_.IsEnd() && step_ == AttackStep::Slash)
	{
		breakTim_.Reset(true);

		// 上方向ベクトル
		Vector3 upDir = -Vector3(std::sinf(animeStatus.rota_.z), std::cosf(animeStatus.rota_.z), 0.0f);
		for (size_t i = 0; i < blades_.size(); i++)
		{
			for (size_t j = 0; j < blades_[i].size(); j++)
			{
				blades_[i][j].StrikeAnimation(upDir);
			}
		}
		
		// 斬撃
		step_ = AttackStep::Strike;
	}

	// 斬撃終了
	if (breakTim_.Ratio() >= 0.75f && step_ == AttackStep::Strike)
	{
		for (size_t i = 0; i < blades_.size(); i++)
		{
			for (size_t j = 0; j < blades_[i].size(); j++)
			{
				blades_[i][j].InitializeAnime(-1, {});
			}
		}

		// 終了
		step_ = AttackStep::None;
	}
}

void SwordDrawer::UpdateColorAnimation()
{
	// 動いているときは濃く
	// 動いていないときは薄く
	alphaPow_.Update(step_ != AttackStep::None);

	float alphaRatio = YMath::EaseInOut<float>(0.0f, 1.0f, alphaPow_.Ratio(), 3.0f);

	handle_.SetAlpha(alphaRatio);
	
	for (size_t i = 0; i < blades_.size(); i++)
	{
		for (size_t j = 0; j < blades_[i].size(); j++)
		{
			blades_[i][j].SetAlpha(alphaRatio);
		}
	}
}

void SwordDrawer::Update()
{
	// アニメーション値保存ステータス
	YGame::YTransform::Status animeStatus;
	
	UpdateAttackAnimation(animeStatus);

	UpdateColorAnimation();

	// トランスフォーム + スプライト更新
	trfm_.UpdateMatrix(animeStatus);

	handle_.Update();

	for (size_t i = 0; i < blades_.size(); i++)
	{
		for (size_t j = 0; j < blades_[i].size(); j++)
		{
			blades_[i][j].Update();
		}
	}
}

void SwordDrawer::Draw()
{
	handle_.Draw();

	for (size_t i = 0; i < blades_.size(); i++)
	{
		for (size_t j = 0; j < blades_[i].size(); j++)
		{
			blades_[i][j].Draw();
		}
	}
}

void SwordDrawer::HandleDrawer::Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent)
{
	BaseInitialize(trfmStatus, matParent);

	sprite_.SetTexture(TextureManager::GetInstance()->GetTexture("Panel"));
}

void SwordDrawer::HandleDrawer::SetAlpha(const float alpha)
{
	sprite_.SetColor(Color(0, 0, 0, 255) * alpha);
}

void SwordDrawer::BladeDrawer::Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent)
{
	drawer_.Initialize(YTransform::Status::Default(), matParent, BlockColorType::None);

	index_ = -1;

	breakStatus_ = {};
	moveSpeed_ = rotaSpeed_ = scaleSpeed_ = {};
}

void SwordDrawer::BladeDrawer::InitializeAnime(const int32_t panelIndex, const YTransform::Status& trfmStatus)
{
	drawer_.SetTransform(trfmStatus);

	index_ = panelIndex;

	isUpdate_ = false;
	breakStatus_ = {};
	moveSpeed_ = rotaSpeed_ = scaleSpeed_ = {};
}

void SwordDrawer::BladeDrawer::StrikeAnimation(const Vector3& upDir)
{
	isUpdate_ = true;
	upDir_ = upDir;

	// 横ベクトル
	Vector3 sideDir = Vector3(0.0f, 0.0f, 1.0f).cross(upDir);

	// ランダムに動き
	float posX = RRandom::RandF(-2.5f, +2.5f);
	float posY = RRandom::RandF(+15.0f, +20.0f);
	moveSpeed_ = (sideDir * posX) + (upDir * posY);

	float rotaZ = RRandom::RandF(-kPI * 0.1f, +kPI * 0.1f);
	rotaSpeed_.z = rotaZ;

	float scale = RRandom::RandF(-1.0f, 0.0f);
	scaleSpeed_ = Vector3(scale, scale, scale);
}

void SwordDrawer::BladeDrawer::Update()
{
	if (isUpdate_)
	{
		// 重力
		moveSpeed_ -= upDir_ * 0.98f;

		breakStatus_.pos_ += moveSpeed_;
		breakStatus_.rota_ += rotaSpeed_;
		breakStatus_.scale_ += scaleSpeed_;

		breakStatus_.scale_.x = std::clamp(breakStatus_.scale_.x, 0.0f, 1.0f);
		breakStatus_.scale_.y = std::clamp(breakStatus_.scale_.y, 0.0f, 1.0f);
		breakStatus_.scale_.z = std::clamp(breakStatus_.scale_.z, 0.0f, 1.0f);
	}

	drawer_.Update(breakStatus_);
}

void SwordDrawer::BladeDrawer::Draw()
{
	drawer_.Draw();
}

void SwordDrawer::BladeDrawer::SetAlpha(const float alpha)
{
	if (index_ == 2)
	{
		drawer_.ChangeColor(BlockColorType::Orange, alpha);
	}
	else
	{
		drawer_.ChangeColor(BlockColorType::None);
	}
}
