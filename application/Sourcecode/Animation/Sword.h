#pragma once
#include "YTransform.h"
#include "SlimeActor.h"
#include "Sprite.h"
#include "Ease.h"

class Sword
{

public:

	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="maxXSize"> : X軸最大値</param>
	/// <param name="maxYSize"> : Y軸最大値</param>
	/// <param name="matParent"> : 親行列</param>
	void Initialize(const size_t maxXSize, const size_t maxYSize, Matrix4* matParent);

	/// <summary>
	/// 攻撃アニメーション
	/// </summary>
	/// <param name="panelIndices"> : パネル番号</param>
	void AttackAnimation(const std::vector<std::vector<int32_t>>& panelIndices);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:

	// 攻撃アニメーション更新
	void UpdateAttackAnimation(YGame::YTransform::Status& animeStatus);

	void UpdateColorAnimation();

private:

	// 持ち手
	struct Handle
	{
		YGame::YTransform trfm_;
		Sprite sprite_;
	};
	
	// パネル
	struct Panel
	{
		int32_t index_;
		YGame::YTransform trfm_;
		Sprite sprite_;
		
		YGame::YTransform::Status breakStatus_;
		Vector3 moveSpeed_;
		Vector3 rotaSpeed_;
		Vector3 scaleSpeed_;
	};

	// 攻撃段階
	enum class AttackStep
	{
		None, Forge, Slash, Strike,
	};

private:

	// 親トランスフォーム
	YGame::YTransform trfm_;

	// 持ち手
	Handle handle_;
	
	// パネル
	std::vector<std::vector<Panel>> panels_;


	// スライムアニメーション用
	YGame::SlimeActor slime_;

	// アニメーション用
	YMath::Ease<float> rotaEas_;
	YMath::YTimer rotaTim_;

	YMath::YPower alphaPow_;

	float panelCounter_ = 0.0f;

	YMath::YTimer breakTim_;
	
	AttackStep step_ = AttackStep::None;
};

