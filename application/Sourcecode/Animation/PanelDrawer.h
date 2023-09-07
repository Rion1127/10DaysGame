#pragma once
#include "BlockDrawer.h"
#include "SlimeActor.h"
#include "Ease.h"

namespace YGame
{
	class PanelDrawer
	{
	
	public:
		
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="trfmStatus"> : トランスフォーム情報</param>
		/// <param name="matParent"> : 親行列</param>
		void Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent);

		/// <summary>
		/// 更新
		/// </summary>
		void Update();

		/// <summary>
		/// 描画
		/// </summary>
		void Draw();

		/// <summary>
		/// アニメーションリセット
		/// </summary>
		void ResetAnime();

		/// <summary>
		/// 色替え
		/// </summary>
		void ChangeColor(const BlockColorType& colorType);

		/// <summary>
		/// 設置アニメーション
		/// </summary>
		void SetAnimation();
		
		/// <summary>
		/// 開放アニメーション
		/// </summary>
		void OpenAnimation();

	private:

		YTransform trfm_;

		BlockDrawer blockDra_;

		SlimeActor slimeActor_;
		
		YMath::Ease<float> rotaEas_;

		YMath::YTimer rotaTim_;

		bool isSet_ = false;
		
		bool isOpen_ = false;
	};
}
