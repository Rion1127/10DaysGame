#pragma once
#include "BaseDrawer.h"

namespace YGame
{
	enum class BlockColorType
	{
		None,	 //	無し (透明)
		
		White,	 //	白
		Gray,	 // 灰色

		Yellow,	 // 黄色 (O)
		Purple,	 // 紫 (T)
		Green,	 // 緑 (S)
		Red,	 // 赤 (Z)
		Cyan,	 // 水色 (I)
		Orange,	 // 橙 (L)
		Blue,	 // 青 (J)
	};

	class BlockDrawer : public BaseDrawer
	{

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="trfmStatus"> : トランスフォーム</param>
		/// <param name="matParent"> : 親行列</param>
		/// <param name="colorType"> : 色</param>
		void Initialize(
			const YTransform::Status& trfmStatus, 
			Matrix4* matParent,
			const BlockColorType& colorType);

		/// <summary>
		/// 色変更
		/// </summary>
		/// <param name="colorType"> : 色</param>
		void ChangeColor(const BlockColorType& colorType);

		/// <summary>
		/// 色取得
		/// </summary>
		/// <returns>現在の色</returns>
		BlockColorType GetColorType() const { return colorType_; }

	private:

		// 色のタイプ
		BlockColorType colorType_ = BlockColorType::Gray;

	};
}
