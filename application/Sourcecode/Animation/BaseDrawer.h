#pragma once
#include "YTransform.h"
#include "Sprite.h"

namespace YGame
{
	// 基底描画クラス
	class BaseDrawer 
	{

	public:
		
		/// <summary>
		/// 更新
		/// </summary>
		void Update(const YTransform::Status& status = {});
		
		/// <summary>
		/// 描画
		/// </summary>
		void Draw();

		/// <summary>
		/// トランスフォーム設定
		/// </summary>
		/// <param name="trfmStatus"> : トランスフォーム情報</param>
		void SetTransform(const YTransform::Status& trfmStatus);

		/// <summary>
		/// アニメリセット
		/// </summary>
		virtual void ResetAnimation() {};

		/// <summary>
		/// 色設定
		/// </summary>
		/// <param name="color"> : 色</param>
		void SetColor(const Color& color) { sprite_.SetColor(color); }
	
	public:

		BaseDrawer() = default;
		
		virtual ~BaseDrawer() = default;
	
	protected:

		// 基底初期化
		void BaseInitialize(const YTransform::Status& trfmStatus, Matrix4* matParent);

		// アニメ更新
		virtual void UpdateAnimation() {};
	
	protected:

		// トランスフォーム
		YTransform trfm_;

		// アニメ変動値
		YTransform::Status animeStatus_;
		
		// アニメ変動値をリセットするか
		bool isResetAnimeStatus_ = true;

		// スプライト
		Sprite sprite_;

	};
}
