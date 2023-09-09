#pragma once
#include "NumberDrawer.h"
#include "YTimer.h"
#include "Ease.h"

namespace YGame
{
	class HPDrawer
	{

	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="trfmStatus"> : �g�����X�t�H�[�����</param>
		/// <param name="matParent"> : �e�s��</param>
		/// <param name="maxHp"> : �ő�HP</param>
		void Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent, const int32_t maxHp);
		
		/// <summary>
		/// �X�V
		/// </summary>
		void Update();
		
		/// <summary>
		/// �`��
		/// </summary>
		void Draw();

		/// <summary>
		/// �ő�HP�ݒ�
		/// </summary>
		/// <param name="maxHp"> : �ő�HP</param>
		void ChangeMaxHPAnimation(const int32_t hp);

		/// <summary>
		/// HP�ݒ�
		/// </summary>
		/// <param name="hp"> : HP</param>
		void ChangeHPAnimation(const int32_t hp);

		int32_t MaxHP() const { return maxHp_; }
		int32_t HP() const { return hp_; }
	
	private:

		// HP�����擾
		float HPRatio();
	
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

		int32_t maxHp_ = 0;
		int32_t hp_ = 0;

		YTransform trfm_;
		std::array<BarDrawer, 3> bars_;
		NumberDrawer number_;

	};
}
