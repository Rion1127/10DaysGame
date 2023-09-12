#pragma once
#include "BaseDrawer.h"
#include "HitActor.h"
#include "DeadActor.h"

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
		void Initialize(const YTransform::Status& trfmStatus, YTransform* pTrfm);

		/// <summary>
		/// �U���A�j���[�V����
		/// </summary>
		void AttackAnimation();

		/// <summary>
		/// ��e�A�j���[�V����
		/// </summary>
		void HitAnimation();

		void DeadAnimation();

		bool GetIsEndAttack() { return isEndAttack_; }

	public:

		EnemyDrawer() = default;

		virtual ~EnemyDrawer() = default;

	private:

		/// <summary>
		/// �A�j���X�V
		/// </summary>
		void UpdateAnimation() override;

	protected:
		
		YTransform* pTrfm_ = nullptr;
	
		// ��e�A�j���[�V����
		HitActor hitActor_;
		DeadActor deadActor_;

		YMath::YTimer moveTim_;

		uint32_t moveCount_;

		YMath::SplineEase<float> attackEas_;

		YMath::YTimer attackTim_;

		bool isEndAttack_ = false;

		YMath::YTimer popTim_;
	};
}
