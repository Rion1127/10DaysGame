#pragma once
#include "Mino.h"
#include "BlockDrawer.h"
#include "SlimeActor.h"

namespace YGame
{
	class NextMinoDrawer
	{
	
	public:
	
		/// <summary>
		/// 初期化
		/// </summary>
		void Initialize();
		
		/// <summary>
		/// 更新
		/// </summary>
		/// <param name="minos"> : 次のミノの情報</param>
		void Update(const std::vector<MinoType>& minos);

		/// <summary>
		/// 描画
		/// </summary>
		void Draw();
	
	private:
		
		// ミノ替え
		void ChangeNextMino(const std::vector<MinoType>& minos);
	
	private:

		class NextMino
		{

		public:

			// 初期化
			void Initialize(const YTransform::Status& trfmStatus);
			
			// 更新
			void Update();

			// 描画
			void Draw();
			
			// ミノ替えアニメ
			void ChangeMinoAnimation(const MinoType type);
			
			// 非表示設定
			void InvisibleMinoAnimation();
		
		private:
			
			YTransform trfm_;

			MinoType type_;

			BlockDrawer drawer_;

			SlimeActor slime_;

			YMath::YTimer colorTim_;

			bool isInvisible_ = false;
		};
		
	private:

		std::vector<MinoType> elderMinos_;

		std::array<NextMino, 5> nextMinos_;
	
	};
}
