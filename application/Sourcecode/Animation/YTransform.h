#pragma once
#include "Vector3.h"
#include "myMath.h"

namespace YGame
{
	// �g�����X�t�H�[�� (�ʒu�A��]�A�傫��)
	struct YTransform
	{
	
	public:
		
		// �ʒu
		Vector3 pos_;
		
		// ��]
		Vector3 rota_;
		
		// �傫��
		Vector3 scale_;
		
		// �s��
		Matrix4 m_;
		
		// �e�s��
		Matrix4* parent_;
	
	public:
		
		// �ݒ�p�X�e�[�^�X
		struct Status
		{

		public:

			// �ʒu
			Vector3 pos_;
			
			// ��]
			Vector3 rota_;
			
			// �傫��
			Vector3 scale_;

		public:

			// �f�t�H���g�l
			static Status Default();

		};

	public:
		
		/// <summary>
		/// ������
		/// </summary>
		/// <param name="status"> : �ݒ�p�X�e�[�^�X</param>
		/// <param name="(Vector3) status.pos_"> : �ʒu</param>
		/// <param name="(Vector3) status.rota_"> : ��]</param>
		/// <param name="(Vector3) status.scale_"> : �傫��</param>
		void Initialize(const Status& status = Status::Default());
		
		/// <summary>
		/// �A�t�B���ϊ�
		/// </summary>
		void UpdateMatrix();
		
		/// <summary>
		/// �A�t�B���ϊ� (�ʒu�A��]�A�傫�� �����Z�����I�u�W�F�N�g�ōs��v�Z)
		/// </summary>
		/// <param name="status"> : �ݒ�p�X�e�[�^�X</param>
		/// <param name="(Vector3) status.pos_"> : �ʒu</param>
		/// <param name="(Vector3) status.rota_"> : ��]</param>
		/// <param name="(Vector3) status.scale_"> : �傫��</param>
		void UpdateMatrix(const Status& status);
	
	public:
		
		YTransform();
		
		/// <summary>
		/// �R���X�g���N�^
		/// </summary>
		/// <param name="status"> : �ݒ�p�X�e�[�^�X</param>
		/// <param name="(Vector3) status.pos_"> : �ʒu</param>
		/// <param name="(Vector3) status.rota_"> : ��]</param>
		/// <param name="(Vector3) status.scale_"> : �傫��</param>
		YTransform(const Status& status);
		
		virtual ~YTransform() = default;
	};
}
