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
		/// �V�[���J�ډ��o
		/// </summary>
		/// <param name="fallFrame"> : ����������</param>
		/// <param name="riseFrame"> : ���J������</param>
		void SceneChangeAnimation(const uint32_t fallFrame, const uint32_t riseFrame);

		/// <summary>
		/// �`��
		/// </summary>
		void Draw();
	
	private:

		struct Block
		{
			YTransform trfm_;
			BlockDrawer drawer_;
			SlimeActor slime_;
		};
	
	private:

		YTransform trfm_;
		std::array<std::array<Block, 10>, 20> blocks_;

		uint32_t fallFrame_;
		uint32_t riseFrame_;
	};
}
