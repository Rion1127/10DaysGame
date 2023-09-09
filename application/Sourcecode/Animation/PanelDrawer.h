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

		void SetTexture(Texture* texture) { blockDra_.SetTexture(texture); }

		/// <summary>
		/// 設置アニメーション
		/// </summary>
		void SetAnimation();
		
		/// <summary>
		/// 開放アニメーション
		/// </summary>
		void OpenAnimation();

		/// <summary>
		/// 有効アニメーション
		/// </summary>
		void ValidAnimtion();

		/// <summary>
		/// 無効アニメーション
		/// </summary>
		void InvalidAnimtion();

	private:

		class LightDrawer : public BaseDrawer
		{
		
		public:
			
			void Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent);

			void SetIsAct(const bool isAct) { isAct_ = isAct; }

			void ResetAnimation() override;
			
		private:

			void UpdateAnimation() override;
		
		private:

			bool isAct_ = false;
			YMath::YPower animePow_;
			YMath::YPower alphaPow_;

			YMath::Ease<float> heightEas_;
			YMath::Ease<float> rotaEas_;
			YMath::Ease<float> scaleEas_;
			YMath::Ease<float> alphaEas_;
		};
	
	private:

		YTransform trfm_;

		BlockDrawer blockDra_;

		LightDrawer lightDra_;

		SlimeActor slimeActor_;
		
		YMath::Ease<float> rotaEas_;

		YMath::YTimer rotaTim_;

		bool isSet_ = false;
		
		bool isOpen_ = false;
	};
}
