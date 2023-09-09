#pragma once
#include "NumberDrawer.h"
#include "YTimer.h"
#include "Ease.h"

namespace YGame
{
	class HPDrawer
	{

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="trfmStatus"> : トランスフォーム情報</param>
		/// <param name="matParent"> : 親行列</param>
		/// <param name="maxHp"> : 最大HP</param>
		void Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent, const int32_t maxHp);
		
		/// <summary>
		/// 更新
		/// </summary>
		void Update();
		
		/// <summary>
		/// 描画
		/// </summary>
		void Draw();

		/// <summary>
		/// 最大HP設定
		/// </summary>
		/// <param name="maxHp"> : 最大HP</param>
		void ChangeMaxHPAnimation(const int32_t hp);

		/// <summary>
		/// HP設定
		/// </summary>
		/// <param name="hp"> : HP</param>
		void ChangeHPAnimation(const int32_t hp);

		int32_t MaxHP() const { return maxHp_; }
		int32_t HP() const { return hp_; }
	
	private:

		// HP割合取得
		float HPRatio();
	
	private:

		class BarDrawer : public BaseDrawer
		{
		
		public:

			void Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent);

			void ChangeRatioAnimation(const float ratio, const uint32_t frame);

		private:
			
			void UpdateAnimation() override;

		private:

			YMath::YTimer changeTim_;
			YMath::Ease<float> changeEas_;		
		};
	
	private:

		int32_t maxHp_ = 0;
		int32_t hp_ = 0;

		YTransform trfm_;
		std::array<BarDrawer, 3> bars_;
		NumberDrawer number_;

	};
}
