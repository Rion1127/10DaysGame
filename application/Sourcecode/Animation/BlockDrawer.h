#pragma once
#include "BaseDrawer.h"

namespace YGame
{
	enum class BlockColorType
	{
		None,	 //	���� (����)
		
		White,	 //	��
		Gray,	 // �D�F

		Yellow,	 // ���F (O)
		Purple,	 // �� (T)
		Green,	 // �� (S)
		Red,	 // �� (Z)
		Cyan,	 // ���F (I)
		Orange,	 // �� (L)
		Blue,	 // �� (J)
	};

	class BlockDrawer : public BaseDrawer
	{

	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="trfmStatus"> : �g�����X�t�H�[��</param>
		/// <param name="matParent"> : �e�s��</param>
		/// <param name="colorType"> : �F</param>
		void Initialize(
			const YTransform::Status& trfmStatus, 
			Matrix4* matParent,
			const BlockColorType& colorType);

		/// <summary>
		/// �F�ύX
		/// </summary>
		/// <param name="colorType"> : �F</param>
		void ChangeColor(const BlockColorType& colorType);

		/// <summary>
		/// �F�擾
		/// </summary>
		/// <returns>���݂̐F</returns>
		BlockColorType GetColorType() const { return colorType_; }

	private:

		// �F�̃^�C�v
		BlockColorType colorType_ = BlockColorType::Gray;

	};
}
