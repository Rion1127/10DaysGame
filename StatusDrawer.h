#pragma once
#include "CountDrawer.h"

namespace YGame
{
	class StatusDrawer
	{

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="trfmStatus"> : トランスフォーム情報</param>
		/// <param name="matParent"> : 親行列</param>
		void Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent);

		/// <summary>
		/// 更新
		/// </summary>
		void Update();

		/// <summary>
		/// パワーアップアニメーション
		/// </summary>
		/// <param name="number"> : 数</param>
		void PowerUpAnimation(const int32_t number);

		/// <summary>
		/// プラスアニメーション
		/// </summary>
		/// <param name="plusNum"> : プラス値</param>
		void PlusAnimation(const int32_t plusNum);

		/// <summary>
		/// 描画
		/// </summary>
		void Draw();
	
	private:

		class SignDrawer : public BaseDrawer
		{
		
		public:

			void Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent);
		};

	private:

		YTransform trfm_;
		
		int32_t number_ = 0;
		CountDrawer counter_;

		YTransform plus_;
		SignDrawer sign_;
		CountDrawer plusCounter_;
		
		YMath::YTimer moveTim_;
		YMath::Ease<float> moveEas_;

	};
}
