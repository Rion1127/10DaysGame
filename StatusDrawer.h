#pragma once
#include "CountDrawer.h"

namespace YGame
{
	class StatusDrawer
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
		/// �p���[�A�b�v�A�j���[�V����
		/// </summary>
		/// <param name="number"> : ��</param>
		void PowerUpAnimation(const int32_t number);

		/// <summary>
		/// �v���X�A�j���[�V����
		/// </summary>
		/// <param name="plusNum"> : �v���X�l</param>
		void PlusAnimation(const int32_t plusNum);

		/// <summary>
		/// �`��
		/// </summary>
		void Draw();
	
	private:

		class SignDrawer : public BaseDrawer
		{
		
		public:

			void Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent);
		};

	private:

		YTransform trfm_;
		
		int32_t number_ = 0;
		CountDrawer counter_;

		YTransform plus_;
		SignDrawer sign_;
		CountDrawer plusCounter_;
		
		YMath::YTimer moveTim_;
		YMath::Ease<float> moveEas_;

	};
}
