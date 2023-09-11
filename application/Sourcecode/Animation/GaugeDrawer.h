#pragma once
#include "CountDrawer.h"

namespace YGame
{
	class GaugeDrawer
	{

	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="trfmStatus"> : �g�����X�t�H�[�����</param>
		/// <param name="matParent"> : �e�s��</param>
		/// <param name="maxValue"> : �ő�l</param>
		void Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent, const int32_t maxValue);

		void SetParent(Matrix4* matParent);
		
		void SetNumberColor(const Color& color);

		/// <summary>
		/// �F�ւ�
		/// </summary>
		/// <param name="color0"> : �F0</param>
		/// <param name="color1"> : �F1</param>
		/// <param name="color2"> : �F2</param>
		void SetGaugeColor(const Color& color0, const Color& color1, const Color& color2);

		/// <summary>
		/// �X�V
		/// </summary>
		void Update();
		
		/// <summary>
		/// �`��
		/// </summary>
		void Draw();

		/// <summary>
		/// �ő�l�ݒ�
		/// </summary>
		/// <param name="maxValue"> : �ő�l</param>
		void ChangeMaxValueAnimation(const int32_t maxValue);

		/// <summary>
		/// �l�ݒ�
		/// </summary>
		/// <param name="value_"> : �l</param>
		void ChangeValueAnimation(const int32_t value);

		int32_t MaxValue() const { return maxValue_; }
		int32_t Value() const { return value_; }
	
	private:

		// �����擾
		float ValueRatio();
	
	private:

		class BarDrawer : public BaseDrawer
		{
		
		public:

			void Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent);

			void ChangeRatioAnimation(const float ratio, const uint32_t frame);

		private:
			
			void UpdateAnimation() override;

		private:

			YMath::YTimer changeTim_;
			YMath::Ease<float> changeEas_;		
		};
	
	private:

		int32_t maxValue_ = 0;
		int32_t value_ = 0;

		YTransform trfm_;
		std::array<BarDrawer, 3> bars_;
		CountDrawer counter_;

	};
}
