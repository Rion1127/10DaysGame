#pragma once
#include "NumberDrawer.h"
#include "YTimer.h"
#include "YPower.h"
#include "Ease.h"

namespace YGame
{
	class RecoveryDrawer : public NumberDrawer
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
		void Update() override;

		/// <summary>
		/// �`��
		/// </summary>
		void Draw() override;

		/// <summary>
		/// �񕜉��o
		/// </summary>
		void RecoverAnimation();

	private:

		// ������
		void CreateDigits() override;

	private:

		class RecoveryDigitDrawer : public DigitDrawer
		{

		public:

			void Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent, const int8_t digit) override;

			void RiseAnimation();

			void SetIsDisp(const bool isDisp) { isDisp_ = isDisp; }

			void ResetAnimation() override;

		private:

			void UpdateAnimation() override;

		protected:

			bool isDisp_ = false;

			YMath::YTimer riseTim_;
			YMath::YPower alphaPow_;
			YMath::Ease<float> riseHeight_;
			YMath::Ease<float> riseScale_;
			YMath::Ease<float> alphaEas_;
		};

		class PlusDrawer : public BaseDrawer
		{

		public:

			void Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent);

			void EmitAnimation();

			void SetIsDisp(const bool isDisp) { isDisp_ = isDisp; }

			void ResetAnimation() override;

		private:

			void UpdateAnimation() override;
		
		private:

			bool isDisp_ = false;

			YMath::YTimer emitTim_;
			YMath::YPower alphaPow_;
			YMath::Ease<float> heightEas_;
			YMath::Ease<float> alphaEas_;
		};

	private:

		YMath::YTimer dispTim_;

		std::array<PlusDrawer, 3> plusDras_;
	
	};
}
