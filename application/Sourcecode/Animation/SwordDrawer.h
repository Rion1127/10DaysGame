#pragma once
#include "BlockDrawer.h"
#include "SlimeActor.h"
#include "Ease.h"

namespace YGame
{
	class SwordDrawer
	{

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="maxXSize"> : X軸最大値</param>
		/// <param name="maxYSize"> : Y軸最大値</param>
		/// <param name="matParent"> : 親行列</param>
		void Initialize(const size_t maxXSize, const size_t maxYSize, Matrix4* matParent);

		/// <summary>
		/// 攻撃アニメーション
		/// </summary>
		/// <param name="panelIndices"> : パネル番号</param>
		void AttackAnimation(const std::vector<std::vector<int32_t>>& panelIndices, const int32_t power);

		/// <summary>
		/// 更新
		/// </summary>
		void Update();

		/// <summary>
		/// 描画
		/// </summary>
		void Draw();
	public:
		bool GetRotaTimEnd() { return rotaTim_.IsEnd(); }

	private:

		// 攻撃アニメーション更新
		void UpdateAttackAnimation(YGame::YTransform::Status& animeStatus);

		// 色アニメーション更新
		void UpdateColorAnimation();

	private:

		// 持ち手
		class HandleDrawer final : public BaseDrawer 
		{
		
		public:

			void Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent);

			void SetAlpha(const float alpha);
		};

		// パネル
		class BladeDrawer final 
		{

		public:

			void Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent);

			void InitializeAnime(const int32_t panelIndex, const YTransform::Status& trfmStatus);
			
			void StrikeAnimation(const Vector3& upDir);

			void Update();
			
			void Draw();

			void SetAlpha(const float alpha);
		
		private:

			BlockDrawer drawer_;

			int32_t index_ = 0;

			bool isUpdate_ = false;
			Vector3 upDir_;
			YTransform::Status breakStatus_;
			Vector3 moveSpeed_;
			Vector3 rotaSpeed_;
			Vector3 scaleSpeed_;
		};

		// 攻撃段階
		enum class AttackStep
		{
			None, Forge, Slash, Strike,
		};

	private:

		YTransform trfm_;
		YTransform bladeTrfm_;

		int32_t power_;

		// 持ち手
		HandleDrawer handle_;

		// パネル
		std::vector<std::vector<BladeDrawer>> blades_;

		// スライムアニメーション用
		YGame::SlimeActor slime_;

		// アニメーション用
		YMath::Ease<float> rotaEas_;
		YMath::YTimer rotaTim_;

		YMath::YPower alphaPow_;

		float panelCounter_ = 0.0f;

		YMath::YTimer breakTim_;

		AttackStep step_ = AttackStep::None;
	};
}
