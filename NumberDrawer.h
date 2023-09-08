#pragma once
#include "DigitDrawer.h"

namespace YGame
{
	class NumberDrawer
	{

	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="trfmStatus"> : �g�����X�t�H�[�����</param>
		/// <param name="matParent"> : �e�s��</param>
		/// <param name="number"> : ��</param>
		virtual void Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent, const int32_t number);

		/// <summary>
		/// �X�V
		/// </summary>
		virtual void Update();

		/// <summary>
		/// �`��
		/// </summary>
		void Draw();

		/// <summary>
		/// ���ݒ�
		/// </summary>
		/// <param name="number"> : ��</param>
		void SetNumber(const int32_t number);
	
	public:

		NumberDrawer() = default;
		virtual ~NumberDrawer() = default;

	protected:

		// ������
		virtual void CreateDigits();
	
	protected:

		int32_t number_ = 0;

		YGame::YTransform trfm_;
		Vector3 offset_;
		std::array<std::unique_ptr<DigitDrawer>, 6> digits_;
	};
}

