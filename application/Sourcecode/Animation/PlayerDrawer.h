#pragma once
#include "BaseDrawer.h"
#include "HitActor.h"
#include "DeadActor.h"

namespace YGame
{
	class PlayerDrawer : public BaseDrawer
	{
		
	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="trfmStatus"> : �g�����X�t�H�[�����</param>
		/// <param name="pTrfm"> : �e�s��</param>
		void Initialize(const YTransform::Status& trfmStatus, YTransform* pTrfm);

		/// <summary>
		/// ��e�A�j���[�V����
		/// </summary>
		void HitAnimation();
		
		/// <summary>
		/// �����A�j���[�V����
		/// </summary>
		void IdleAnimation();
		
		/// <summary>
		/// �ړ��A�j���[�V����
		/// </summary>
		void MoveAnimation();

		void DeadAnimation();

	public:

		PlayerDrawer() = default;
		
		virtual ~PlayerDrawer() = default;

	private:

		// �e�N�X�`��
		enum class TextureType
		{
			Idle, Move
		};
	
	private:

		// �e�N�X�`���ύX
		void ChangeTexture(const TextureType textureType);

		// �A�j���X�V
		void UpdateAnimation() override;

	protected:

		YTransform* pTrfm_ = nullptr;

		// ��e�A�j���[�V����
		HitActor hitActor_;

		DeadActor dead_;

		bool isIdle_ = false;
		
		bool isMove_ = false;

		YMath::YTimer moveTim_;

		uint32_t moveCount_;
	};
}
