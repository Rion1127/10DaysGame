#pragma once
#include "Mino.h"
#include "BlockDrawer.h"
#include "SlimeActor.h"

namespace YGame
{
	class NextMinoDrawer
	{
	
	public:
	
		/// <summary>
		/// ������
		/// </summary>
		void Initialize();
		
		/// <summary>
		/// �X�V
		/// </summary>
		/// <param name="minos"> : ���̃~�m�̏��</param>
		void Update(const std::vector<MinoType>& minos);

		/// <summary>
		/// �`��
		/// </summary>
		void Draw();
	
	private:
		
		// �~�m�ւ�
		void ChangeNextMino(const std::vector<MinoType>& minos);
	
	private:

		class NextMino
		{

		public:

			// ������
			void Initialize(const YTransform::Status& trfmStatus);
			
			// �X�V
			void Update();

			// �`��
			void Draw();
			
			// �~�m�ւ��A�j��
			void ChangeMinoAnimation(const MinoType type);
			
			// ��\���ݒ�
			void InvisibleMinoAnimation();
		
		private:
			
			YTransform trfm_;

			MinoType type_;

			BlockDrawer drawer_;

			SlimeActor slime_;

			YMath::YTimer colorTim_;

			bool isInvisible_ = false;
		};
		
	private:

		std::vector<MinoType> elderMinos_;

		std::array<NextMino, 5> nextMinos_;
	
	};
}
