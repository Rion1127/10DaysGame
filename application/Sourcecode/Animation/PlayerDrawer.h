#pragma once
#include "BaseDrawer.h"
#include "HitActor.h"

namespace YGame
{
	class PlayerDrawer : public BaseDrawer
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

		PlayerDrawer() = default;
		
		virtual ~PlayerDrawer() = default;

	private:

		/// <summary>
		/// アニメ更新
		/// </summary>
		void UpdateAnimation() override;

	protected:

		// 被弾アニメーション
		HitActor hitActor_;

	};
}
