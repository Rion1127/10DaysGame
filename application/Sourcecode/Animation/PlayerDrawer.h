#pragma once
#include "BaseDrawer.h"
#include "HitActor.h"
#include "DeadActor.h"

namespace YGame
{
	class PlayerDrawer : public BaseDrawer
	{
		
	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="trfmStatus"> : トランスフォーム情報</param>
		/// <param name="pTrfm"> : 親行列</param>
		void Initialize(const YTransform::Status& trfmStatus, YTransform* pTrfm);

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

		void DeadAnimation();

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

		YTransform* pTrfm_ = nullptr;

		// 被弾アニメーション
		HitActor hitActor_;

		DeadActor dead_;

		bool isIdle_ = false;
		
		bool isMove_ = false;

		YMath::YTimer moveTim_;

		uint32_t moveCount_;
	};
}
