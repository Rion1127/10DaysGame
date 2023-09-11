#pragma once
#include "CountDrawer.h"

namespace YGame
{
	class MinoCounterDrawer
	{
	
	public:

		/// <summary>
		/// 初期化
		/// </summary>
		void Initialize();
		
		/// <summary>
		/// 更新
		/// </summary>
		void Update(const int32_t countNum);

		/// <summary>
		/// 描画
		/// </summary>
		void Draw();

	private:

		int32_t elder_ = 0;

		CountDrawer counter_;
	
	};
}
