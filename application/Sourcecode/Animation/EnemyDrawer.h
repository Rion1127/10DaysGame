#pragma once
#include "BaseDrawer.h"
#include "HitActor.h"
#include "DeadActor.h"

namespace YGame
{
	enum EnemyType
	{
		Slime, Bat, Bear,
	};
	
	class EnemyDrawer : public BaseDrawer
	{

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="trfmStatus"> : トランスフォーム情報</param>
		/// <param name="matParent"> : 親行列</param>
		void Initialize(const YTransform::Status& trfmStatus, YTransform* pTrfm, const EnemyType type);

		/// <summary>
		/// 攻撃アニメーション
		/// </summary>
		void AttackAnimation();

		/// <summary>
		/// 被弾アニメーション
		/// </summary>
		void HitAnimation();

		void DeadAnimation();

		bool GetIsEndAttack() { return isEndAttack_; }

	public:

		EnemyDrawer() = default;

		virtual ~EnemyDrawer() = default;

	private:

		/// <summary>
		/// アニメ更新
		/// </summary>
		void UpdateAnimation() override;

	protected:
		
		YTransform* pTrfm_ = nullptr;
	
		// 被弾アニメーション
		HitActor hitActor_;
		DeadActor deadActor_;

		YMath::YTimer moveTim_;

		uint32_t moveCount_;

		YMath::SplineEase<float> attackEas_;

		YMath::YTimer attackTim_;

		bool isEndAttack_ = false;

		YMath::YTimer popTim_;
	};
}
