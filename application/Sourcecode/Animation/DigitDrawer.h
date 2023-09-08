#pragma once
#include "BaseDrawer.h"

namespace YGame
{
	class DigitDrawer : public BaseDrawer
	{

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="trfmStatus"> : トランスフォーム情報</param>
		/// <param name="matParent"> : 親行列</param>
		/// <param name="digit"> : 数</param>
		virtual void Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent, const int8_t digit);

		/// <summary>
		/// 数設定
		/// </summary>
		/// <param name="digit"> : 数</param>
		void SetDigit(const int8_t digit);

		/// <summary>
		/// 非表示設定
		/// </summary>
		/// <param name="isInvisible"> : 非表示フラグ</param>
		void SetInvisible(const bool isInvisible) { sprite_.SetInvisivle(isInvisible); }
	
	public:

		DigitDrawer() = default;
		virtual ~DigitDrawer() = default;
	
	protected:

		int32_t digit_ = 0;
	};
}
