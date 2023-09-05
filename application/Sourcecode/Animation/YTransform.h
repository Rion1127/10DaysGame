#pragma once
#include "Vector3.h"
#include "myMath.h"

namespace YGame
{
	// トランスフォーム (位置、回転、大きさ)
	struct YTransform
	{
	
	public:
		
		// 位置
		Vector3 pos_;
		
		// 回転
		Vector3 rota_;
		
		// 大きさ
		Vector3 scale_;
		
		// 行列
		Matrix4 m_;
		
		// 親行列
		Matrix4* parent_;
	
	public:
		
		// 設定用ステータス
		struct Status
		{

		public:

			// 位置
			Vector3 pos_;
			
			// 回転
			Vector3 rota_;
			
			// 大きさ
			Vector3 scale_;

		public:

			// デフォルト値
			static Status Default();

		};

	public:
		
		/// <summary>
		/// 初期化
		/// </summary>
		/// <param name="status"> : 設定用ステータス</param>
		/// <param name="(Vector3) status.pos_"> : 位置</param>
		/// <param name="(Vector3) status.rota_"> : 回転</param>
		/// <param name="(Vector3) status.scale_"> : 大きさ</param>
		void Initialize(const Status& status = Status::Default());
		
		/// <summary>
		/// アフィン変換
		/// </summary>
		void UpdateMatrix();
		
		/// <summary>
		/// アフィン変換 (位置、回転、大きさ を加算したオブジェクトで行列計算)
		/// </summary>
		/// <param name="status"> : 設定用ステータス</param>
		/// <param name="(Vector3) status.pos_"> : 位置</param>
		/// <param name="(Vector3) status.rota_"> : 回転</param>
		/// <param name="(Vector3) status.scale_"> : 大きさ</param>
		void UpdateMatrix(const Status& status);
	
	public:
		
		YTransform();
		
		/// <summary>
		/// コンストラクタ
		/// </summary>
		/// <param name="status"> : 設定用ステータス</param>
		/// <param name="(Vector3) status.pos_"> : 位置</param>
		/// <param name="(Vector3) status.rota_"> : 回転</param>
		/// <param name="(Vector3) status.scale_"> : 大きさ</param>
		YTransform(const Status& status);
		
		virtual ~YTransform() = default;
	};
}
