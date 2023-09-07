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
	
	public:

		BaseDrawer() = default;
		
		virtual ~BaseDrawer() = default;
	
	protected:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="trfmStatus"> : トランスフォーム情報</param>
		/// <param name="matParent"> : 親行列</param>
		void BaseInitialize(const YTransform::Status& trfmStatus, Matrix4* matParent);

		/// <summary>
		/// アニメ更新
		/// </summary>
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
