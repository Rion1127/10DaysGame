#pragma once
#include "BaseDrawer.h"
#include "HitActor.h"
#include "YTimer.h"

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
		
		/// <summary>
		/// 立ちアニメーション
		/// </summary>
		void IdleAnimation();
		
		/// <summary>
		/// 移動アニメーション
		/// </summary>
		void MoveAnimation();

	public:

		PlayerDrawer() = default;
		
		virtual ~PlayerDrawer() = default;

	private:

		// テクスチャ
		enum class TextureType
		{
			Idle, Move
		};
	
	private:

		// テクスチャ変更
		void ChangeTexture(const TextureType textureType);

		// アニメ更新
		void UpdateAnimation() override;

	protected:

		// 被弾アニメーション
		HitActor hitActor_;

		bool isIdle_ = false;
		
		bool isMove_ = false;

		YMath::YTimer moveTim_;

		uint32_t moveCount_;
	};
}
