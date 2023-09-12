#pragma once
#include "DigitDrawer.h"

namespace YGame
{
	class NumberDrawer
	{

	public:

		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="trfmStatus"> : トランスフォーム情報</param>
		/// <param name="matParent"> : 親行列</param>
		/// <param name="number"> : 数</param>
		virtual void Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent, const int32_t number);

		/// <summary>
		/// 更新
		/// </summary>
		virtual void Update(const YTransform::Status& animeStatus = {});

		/// <summary>
		/// 描画
		/// </summary>
		virtual void Draw();

		/// <summary>
		/// 数設定
		/// </summary>
		/// <param name="number"> : 数</param>
		void SetNumber(const int32_t number);

		void SetColor(const Color& color);

		int32_t GetNumber() { return number_; }
	
	public:

		NumberDrawer() = default;
		virtual ~NumberDrawer() = default;

	protected:

		// 数生成
		virtual void CreateDigits();
	
	protected:

		int32_t number_ = 0;

		YTransform trfm_;

		Vector3 offset_;
		std::array<std::unique_ptr<DigitDrawer>, 6> digits_;
	};
}

