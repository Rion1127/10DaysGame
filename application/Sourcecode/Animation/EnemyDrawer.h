#pragma once
#include "BaseDrawer.h"
#include "HitActor.h"
#include "YTimer.h"

namespace YGame
{
	class EnemyDrawer : public BaseDrawer
	{

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="trfmStatus"> : トランスフォーム情報</param>
		/// <param name="matParent"> : 親行列</param>
		void Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent);

		/// <summary>
		/// 被弾アニメーション
		/// </summary>
		void HitAnimation();

	public:

		EnemyDrawer() = default;

		virtual ~EnemyDrawer() = default;

	private:

		/// <summary>
		/// アニメ更新
		/// </summary>
		void UpdateAnimation() override;

	protected:

		// 被弾アニメーション
		HitActor hitActor_;

		YMath::YTimer moveTim_;

		uint32_t moveCount_;
	};
}
