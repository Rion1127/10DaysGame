#pragma once
#include "NumberDrawer.h"
#include "YTimer.h"
#include "YPower.h"
#include "Ease.h"
#include "SplineEase.h"

namespace YGame
{
	class CountDrawer : public NumberDrawer
	{

	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="trfmStatus"> : �g�����X�t�H�[�����</param>
		/// <param name="matParent"> : �e�s��</param>
		/// <param name="number"> : ��</param>
		void Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent, const int32_t number) override;
		
		/// <summary>
		/// �ω��A�j���[�V����
		/// </summary>
		/// <param name="number"> : ��</param>
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
}

