#pragma once
#include "BaseDrawer.h"
#include "HitActor.h"
#include "YTimer.h"

namespace YGame
{
	class EnemyDrawer : public BaseDrawer
	{

	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="trfmStatus"> : �g�����X�t�H�[�����</param>
		/// <param name="matParent"> : �e�s��</param>
		void Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent);

		/// <summary>
		/// ��e�A�j���[�V����
		/// </summary>
		void HitAnimation();

	public:

		EnemyDrawer() = default;

		virtual ~EnemyDrawer() = default;

	private:

		/// <summary>
		/// �A�j���X�V
		/// </summary>
		void UpdateAnimation() override;

	protected:

		// ��e�A�j���[�V����
		HitActor hitActor_;

		YMath::YTimer moveTim_;

		uint32_t moveCount_;
	};
}
