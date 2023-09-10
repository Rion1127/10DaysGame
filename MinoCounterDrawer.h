#pragma once
#include "NumberDrawer.h"
#include "YTimer.h"
#include "YPower.h"
#include "Ease.h"
#include "SplineEase.h"

namespace YGame
{
	class MinoCounterDrawer
	{
	
	public:

		/// <summary>
		/// èâä˙âª
		/// </summary>
		void Initialize();
		
		/// <summary>
		/// çXêV
		/// </summary>
		void Update(const int32_t countNum);

		/// <summary>
		/// ï`âÊ
		/// </summary>
		void Draw();

	private:

		class CountDrawer : public NumberDrawer
		{

		public:

			void Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent, const int32_t number) override;
			void ChangeAnimation(const int32_t number);

		private:

			void CreateDigits() override;

		private:

			class CountDigitDrawer : public DigitDrawer
			{

			public:

				void Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent, const int8_t digit) override;
				void JumpAnimation();
				void ResetAnimation() override;

			private:

				void UpdateAnimation() override;

			protected:

				YMath::YTimer jumpTim_;
				YMath::SplineEase<float> jumpHeight_;
			};

		private:

			int32_t elder_ = 0;

		};

	private:

		int32_t elder_ = 0;

		CountDrawer counter_;
	
	};
}
