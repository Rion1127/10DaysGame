#pragma once
#include "CountDrawer.h"

namespace YGame
{
	class GaugeDrawer
	{

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="trfmStatus"> : トランスフォーム情報</param>
		/// <param name="matParent"> : 親行列</param>
		/// <param name="maxValue"> : 最大値</param>
		void Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent, const int32_t maxValue);

		void SetParent(Matrix4* matParent);
		
		void SetNumberColor(const Color& color);

		/// <summary>
		/// 色替え
		/// </summary>
		/// <param name="color0"> : 色0</param>
		/// <param name="color1"> : 色1</param>
		/// <param name="color2"> : 色2</param>
		void SetGaugeColor(const Color& color0, const Color& color1, const Color& color2);

		/// <summary>
		/// 更新
		/// </summary>
		void Update();
		
		/// <summary>
		/// 描画
		/// </summary>
		void Draw();

		/// <summary>
		/// 最大値設定
		/// </summary>
		/// <param name="maxValue"> : 最大値</param>
		void ChangeMaxValueAnimation(const int32_t maxValue);

		/// <summary>
		/// 値設定
		/// </summary>
		/// <param name="value_"> : 値</param>
		void ChangeValueAnimation(const int32_t value);

		int32_t MaxValue() const { return maxValue_; }
		int32_t Value() const { return value_; }
	
	private:

		// 割合取得
		float ValueRatio();
	
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

		int32_t maxValue_ = 0;
		int32_t value_ = 0;

		YTransform trfm_;
		std::array<BarDrawer, 3> bars_;
		CountDrawer counter_;

	};
}
