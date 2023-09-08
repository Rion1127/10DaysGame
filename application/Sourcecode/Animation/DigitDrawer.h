#pragma once
#include "BaseDrawer.h"

namespace YGame
{
	class DigitDrawer : public BaseDrawer
	{

	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="trfmStatus"> : �g�����X�t�H�[�����</param>
		/// <param name="matParent"> : �e�s��</param>
		/// <param name="digit"> : ��</param>
		virtual void Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent, const int8_t digit);

		/// <summary>
		/// ���ݒ�
		/// </summary>
		/// <param name="digit"> : ��</param>
		void SetDigit(const int8_t digit);

		/// <summary>
		/// ��\���ݒ�
		/// </summary>
		/// <param name="isInvisible"> : ��\���t���O</param>
		void SetInvisible(const bool isInvisible) { sprite_.SetInvisivle(isInvisible); }
	
	public:

		DigitDrawer() = default;
		virtual ~DigitDrawer() = default;
	
	protected:

		int32_t digit_ = 0;
	};
}
