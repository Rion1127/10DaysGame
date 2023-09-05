#pragma once
#include "Shake.h"
#include "Color.h"
#include <cstdint>

namespace YGame
{
	class HitActor
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
		/// 被弾
		/// </summary>
		/// <param name="swing"> : 揺れ</param>
		/// <param name="dekey"> : 減衰値</param>
		/// <param name="place"> : 位</param>
		void Hit(const float swing, const float dekey);

	public:
		
		/// <summary>
		/// 動作中か
		/// </summary>
		/// <returns>動作フラグ</returns>
		inline bool IsAct() const { return isAct_; }

		/// <summary>
		/// 揺れ値取得
		/// </summary>
		/// <returns>揺れ値</returns>
		inline Vector3 ShakePosValue() const { return shake_.Value(); }

		/// <summary>
		/// ヒット時の色
		/// </summary>
		/// <returns></returns>
		inline Color ColorValue() const { return colorValue_; }

	public:

		HitActor() = default;
		
		virtual ~HitActor() = default;
	
	private:

		// 動いているかフラグ
		bool isAct_ = false;
		
		// 揺れ
		YMath::Shake shake_;

		// 色
		Color colorValue_;
	};
}
