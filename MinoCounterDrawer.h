#pragma once
#include "CountDrawer.h"

namespace YGame
{
	class MinoCounterDrawer
	{
	
	public:

		/// <summary>
		/// ������
		/// </summary>
		void Initialize();
		
		/// <summary>
		/// �X�V
		/// </summary>
		void Update(const int32_t countNum);

		/// <summary>
		/// �`��
		/// </summary>
		void Draw();

	private:

		int32_t elder_ = 0;

		CountDrawer counter_;
	
	};
}
