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
		/// ������
		/// </summary>
		/// <param name="trfmStatus"> : �g�����X�t�H�[�����</param>
		/// <param name="matParent"> : �e�s��</param>
		void Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent);

		/// <summary>
		/// �X�V
		/// </summary>
		void Update();

		/// <summary>
		/// �`��
		/// </summary>
		void Draw();

		/// <summary>
		/// �A�j���[�V�������Z�b�g
		/// </summary>
		void ResetAnime();

		/// <summary>
		/// �F�ւ�
		/// </summary>
		void ChangeColor(const BlockColorType& colorType);

		void SetTexture(Texture* texture) { blockDra_.SetTexture(texture); }

		/// <summary>
		/// �ݒu�A�j���[�V����
		/// </summary>
		void SetAnimation();
		
		/// <summary>
		/// �J���A�j���[�V����
		/// </summary>
		void OpenAnimation();

		/// <summary>
		/// �L���A�j���[�V����
		/// </summary>
		void ValidAnimtion();

		/// <summary>
		/// �����A�j���[�V����
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
