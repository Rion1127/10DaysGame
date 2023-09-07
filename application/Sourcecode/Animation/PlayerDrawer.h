#pragma once
#include "BaseDrawer.h"
#include "HitActor.h"
#include "YTimer.h"

namespace YGame
{
	class PlayerDrawer : public BaseDrawer
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
		
		/// <summary>
		/// �����A�j���[�V����
		/// </summary>
		void IdleAnimation();
		
		/// <summary>
		/// �ړ��A�j���[�V����
		/// </summary>
		void MoveAnimation();

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

		// ��e�A�j���[�V����
		HitActor hitActor_;

		bool isIdle_ = false;
		
		bool isMove_ = false;

		YMath::YTimer moveTim_;

		uint32_t moveCount_;
	};
}
