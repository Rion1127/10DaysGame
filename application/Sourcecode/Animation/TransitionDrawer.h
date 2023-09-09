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
		/// 幕引き演出
		/// </summary>
		/// <param name="frame"> : 時間</param>
		/// <param name="phaseNum"> : フェーズ数</param>
		void SceneChangeAnimation(const uint32_t frame, const uint32_t phaseNum);

		/// <summary>
		/// 描画
		/// </summary>
		void Draw();

		/// <summary>
		/// 遷移する瞬間
		/// </summary>
		/// <returns></returns>
		bool IsChangeMoment() const { return isChangeMoment_; }
	
	private:

		// 幕引きアニメーション
		void FallAnimation();
		
		// 幕開けアニメーション
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
