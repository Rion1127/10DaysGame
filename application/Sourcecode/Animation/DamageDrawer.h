#pragma once
#include "NumberDrawer.h"
#include "YTimer.h"
#include "YPower.h"
#include "SplineEase.h"
#include "Ease.h"

namespace YGame
{
	class DamageDrawer : public NumberDrawer
	{
	
	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="trfmStatus"> : トランスフォーム情報</param>
		/// <param name="matParent"> : 親行列</param>
		/// <param name="number"> : 数</param>
		void Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent, const int32_t number) override;
		
		/// <summary>
		/// 更新
		/// </summary>
		void Update(const YTransform::Status& animeStatus = {}) override;

		/// <summary>
		/// ダメージアニメーション
		/// </summary>
		void DamageAnimation();
	
	private:
		
		// 数生成
		void CreateDigits() override;

	private:

		class DamageDigitDrawer : public DigitDrawer
		{

		public:

			void Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent, const int8_t digit) override;

			void PopAnimation();

			void SetIsDisp(const bool isDisp) { isDisp_ = isDisp; }

		private:

			void ResetAnimation() override;

			void UpdateAnimation() override;

		protected:
			
			bool isDisp_ = false;

			YMath::YTimer popTim_;
			YMath::YPower alphaPow_;
			YMath::SplineEase<float> popHeight_;
			YMath::Ease<float> popScale_;
			YMath::Ease<float> alphaEas_;
		};
	
	private:

		YMath::YTimer dispTim_;
		
		YMath::YTimer emitTim_;
		size_t emitCounter_;
	
	};
}
