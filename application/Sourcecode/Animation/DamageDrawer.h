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
		/// ������
		/// </summary>
		/// <param name="trfmStatus"> : �g�����X�t�H�[�����</param>
		/// <param name="matParent"> : �e�s��</param>
		/// <param name="number"> : ��</param>
		void Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent, const int32_t number) override;
		
		/// <summary>
		/// �X�V
		/// </summary>
		void Update(const YTransform::Status& animeStatus = {}) override;

		/// <summary>
		/// �_���[�W�A�j���[�V����
		/// </summary>
		void DamageAnimation();
	
	private:
		
		// ������
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
