#pragma once
#include "BlockDrawer.h"
#include "SlimeActor.h"

namespace YGame
{
	class TransitionDrawer
	{

	public:

		/// <summary>
		/// ������
		/// </summary>
		void Initialize();

		/// <summary>
		/// �X�V
		/// </summary>
		void Update();

		/// <summary>
		/// ���������o
		/// </summary>
		/// <param name="frame"> : ����</param>
		/// <param name="phaseNum"> : �t�F�[�Y��</param>
		void SceneChangeAnimation(const uint32_t frame, const uint32_t phaseNum);

		/// <summary>
		/// �`��
		/// </summary>
		void Draw();

		/// <summary>
		/// �J�ڂ���u��
		/// </summary>
		/// <returns></returns>
		bool IsChangeMoment() const { return isChangeMoment_; }
	
	private:

		// �������A�j���[�V����
		void FallAnimation();
		
		// ���J���A�j���[�V����
		void RiseAnimation();
	
	private:

		struct Block
		{
			YTransform trfm_;
			BlockDrawer drawer_;
			SlimeActor slime_;
			bool isExpand_ = false;
			bool isContract_ = false;
		};

		enum class Phase
		{
			Fall, Rise
		};
	
	private:

		YTransform trfm_;
		std::array<std::array<Block, 10>, 20> blocks_;
		
		bool isTransition_ = true;

		YMath::YTimer intervalTim_;
		
		Phase phase_ = Phase::Fall;
		uint32_t phaseNum_ = 0;
		uint32_t phaseCounter_ = 0;

		bool isChangeMoment_ = false;
	};
}
