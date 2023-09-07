#pragma once
#include "YTransform.h"
#include "Sprite.h"

namespace YGame
{
	// ���`��N���X
	class BaseDrawer 
	{

	public:
		
		/// <summary>
		/// �X�V
		/// </summary>
		void Update(const YTransform::Status& status = {});
		
		/// <summary>
		/// �`��
		/// </summary>
		void Draw();

		/// <summary>
		/// �g�����X�t�H�[���ݒ�
		/// </summary>
		/// <param name="trfmStatus"> : �g�����X�t�H�[�����</param>
		void SetTransform(const YTransform::Status& trfmStatus);
	
	public:

		BaseDrawer() = default;
		
		virtual ~BaseDrawer() = default;
	
	protected:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="trfmStatus"> : �g�����X�t�H�[�����</param>
		/// <param name="matParent"> : �e�s��</param>
		void BaseInitialize(const YTransform::Status& trfmStatus, Matrix4* matParent);

		/// <summary>
		/// �A�j���X�V
		/// </summary>
		virtual void UpdateAnimation() {};
	
	protected:

		// �g�����X�t�H�[��
		YTransform trfm_;

		// �A�j���ϓ��l
		YTransform::Status animeStatus_;
		
		// �A�j���ϓ��l�����Z�b�g���邩
		bool isResetAnimeStatus_ = true;

		// �X�v���C�g
		Sprite sprite_;

	};
}
