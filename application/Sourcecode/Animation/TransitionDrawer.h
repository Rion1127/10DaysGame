#pragma once
#include "BlockDrawer.h"
#include "SlimeActor.h"

namespace YGame
{
	class TransitionDrawer
	{

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		void Initialize();

		/// <summary>
		/// 更新
		/// </summary>
		void Update();

		/// <summary>
		/// シーン遷移演出
		/// </summary>
		/// <param name="fallFrame"> : 幕引き時間</param>
		/// <param name="riseFrame"> : 幕開け時間</param>
		void SceneChangeAnimation(const uint32_t fallFrame, const uint32_t riseFrame);

		/// <summary>
		/// 描画
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
