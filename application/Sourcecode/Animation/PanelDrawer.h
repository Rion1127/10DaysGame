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

		/// <summary>
		/// �ݒu�A�j���[�V����
		/// </summary>
		void SetAnimation();
		
		/// <summary>
		/// �J���A�j���[�V����
		/// </summary>
		void OpenAnimation();

	private:

		YTransform trfm_;

		BlockDrawer blockDra_;

		SlimeActor slimeActor_;
		
		YMath::Ease<float> rotaEas_;

		YMath::YTimer rotaTim_;

		bool isSet_ = false;
		
		bool isOpen_ = false;
	};
}
