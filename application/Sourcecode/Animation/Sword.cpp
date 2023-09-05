#include "Sword.h"
#include "Lerp.h"
#include "YCameraManager.h"

static const float kPI = 3.141592f;

void Sword::Initialize(const size_t maxXSize, const size_t maxYSize, Matrix4* matParent)
{
	// 親トランスフォーム
	trfm_.Initialize();
	trfm_.parent_ = matParent;

	// ハンドル
	handle_.trfm_.Initialize();
	handle_.trfm_.parent_ = &trfm_.m_;
	handle_.trfm_.pos_ = Vector3(0.0f, -16.0f, 0.0f);
	handle_.trfm_.scale_ = Vector3(0.25f, 1.0f, 0.0f);
	handle_.sprite_.Ini();
	handle_.sprite_.SetTexture(TextureManager::GetInstance()->GetTexture("Panel"));

	// パネル縦横分生成
	for (size_t y = 0; y < maxYSize; y++)
	{
		panels_.emplace_back();
		for (size_t x = 0; x < maxXSize; x++)
		{
			panels_[y].emplace_back();
			
			panels_[y][x].trfm_.Initialize();
			panels_[y][x].trfm_.parent_ = &trfm_.m_;

			panels_[y][x].sprite_.Ini();
			
			panels_[y][x].sprite_.SetTexture(TextureManager::GetInstance()->GetTexture("Panel"));
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

	step_ = AttackStep::None;
}

void Sword::AttackAnimation(const std::vector<std::vector<int32_t>>& panelIndices)
{
	panelCounter_ = 0.0f;

	static const float kPanelSize = 32.0f;
	static const float kPanelScale = 0.5f;
	
	size_t xSize = panelIndices.size(), ySize = panelIndices[0].size();

	for (size_t i = 0; i < panelIndices.size(); i++)
	{
		for (size_t j = 0; j < panelIndices[i].size(); j++)
		{
			panels_[i][j].index_ = panelIndices[i][j];

			Vector3 leftTop = -Vector3(kPanelSize * xSize, kPanelSize * ySize, 0.0f) * kPanelScale / 2.0f;
			leftTop -= Vector3(0.0f, kPanelSize * ySize, 0.0f) * kPanelScale / 2.0f;

			panels_[i][j].trfm_.pos_ = Vector3(kPanelSize * i, kPanelSize * j, 0) * kPanelScale + leftTop;
			panels_[i][j].trfm_.scale_ = Vector3(kPanelScale, kPanelScale, 0);

			if (panels_[i][j].index_ == 2)
			{
				panelCounter_ += 1.0f;
			}
		}
	}

	slime_.Wobble();

	rotaTim_.Reset();

	// 生成
	step_ = AttackStep::Forge;
}

void Sword::UpdateAttackAnimation(YGame::YTransform::Status& animeStatus)
{
	slime_.Update();

	rotaTim_.Update();

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
		// 斬撃
		step_ = AttackStep::Strike;

		float shake = panelCounter_ * 2.0f;
		float dekey = shake / 10.0f;

		YCameraManager::GetInstance()->ShakeCamera(shake, dekey);
	}

	// 斬撃終了
	if (rotaTim_.IsEnd() && step_ == AttackStep::Strike)
	{
		// 終了
		step_ = AttackStep::None;
	}
}

void Sword::UpdateColorAnimation()
{
	// 動いているときは濃く
	// 動いていないときは薄く
	alphaPow_.Update(step_ != AttackStep::None);

	float alphaRatio = YMath::EaseInOut<float>(0.0f, 1.0f, alphaPow_.Ratio(), 3.0f);
	
	handle_.sprite_.SetColor(Color(0, 0, 0, 255) * alphaRatio);
	
	for (size_t i = 0; i < panels_.size(); i++)
	{
		for (size_t j = 0; j < panels_[i].size(); j++)
		{
			if (panels_[i][j].index_ == 2)
			{
				panels_[i][j].sprite_.SetColor(Color(0, 255, 0, 255) * alphaRatio);
			}
			else
			{
				panels_[i][j].sprite_.SetColor(Color(0, 0, 0, 0));
			}
		}
	}
}

void Sword::Update()
{
	// アニメーション値保存ステータス
	YGame::YTransform::Status animeStatus;
	
	UpdateAttackAnimation(animeStatus);

	UpdateColorAnimation();

	// トランスフォーム + スプライト更新
	trfm_.UpdateMatrix(animeStatus);

	handle_.trfm_.UpdateMatrix();
	handle_.sprite_.Update(handle_.trfm_.m_);

	for (size_t i = 0; i < panels_.size(); i++)
	{
		for (size_t j = 0; j < panels_[i].size(); j++)
		{
			panels_[i][j].trfm_.UpdateMatrix();

			panels_[i][j].sprite_.Update(panels_[i][j].trfm_.m_);
		}
	}
}

void Sword::Draw()
{
	handle_.sprite_.Draw();

	for (size_t i = 0; i < panels_.size(); i++)
	{
		for (size_t j = 0; j < panels_[i].size(); j++)
		{
			panels_[i][j].sprite_.Draw();
		}
	}
}
