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
		/// �`��
		/// </summary>
		void Draw() override;

		/// <summary>
		/// �_���[�W�A�j���[�V����
		/// </summary>
		void DamageAnimation();

		/// <summary>
		/// ��S�̈ꌂ�A�j���[�V����
		/// </summary>
		void CriticalAnimation();
	
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
			void SetIsCritical(const bool isCritical) { isCritical_ = isCritical; }
		private:
			void ResetAnimation() override;
			void UpdateAnimation() override;
		private:
			bool isDisp_ = false;
			bool isCritical_ = false;
			YMath::YTimer popTim_;
			YMath::YPower alphaPow_;
			YMath::SplineEase<float> popHeight_;
			YMath::Ease<float> popScale_;
			YMath::Ease<float> alphaEas_;
		};

		class CriticalDrawer
		{
		public:
			void Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent);
			void ResetAnimation();
			void PopAnimation();
			void Update();
			void DrawBack();
			void DrawFront();
			void SetIsDisp(const bool isDisp) { isDisp_ = isDisp; }
		private:
			class CriticalFontDrawer : public BaseDrawer
			{
			public:
				void Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent);
			};
			class CriticalEffectDrawer : public BaseDrawer
			{
			public:
				void Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent);
			};
		private:
			YTransform trfm_;
			CriticalFontDrawer font_;
			CriticalEffectDrawer effect_;

			bool isDisp_ = false;
			YMath::YTimer popTim_;
			YMath::YPower alphaPow_;
			YMath::Ease<float> popScale_;
			YMath::Ease<float> alphaEas_;
		};

	private:

		YMath::YTimer dispTim_;
		
		YMath::YTimer emitTim_;
		size_t emitCounter_;

		CriticalDrawer critical_;
	
	};
}
