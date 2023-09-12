#pragma once
#include "CountDrawer.h"

namespace YGame
{
	class WallDrawer
	{

	public:

		void Initialize();

		void Update();

		void Draw();

		void ChangePlusHealth(const int32_t plusNum);
		void ChangePlusAttack(const int32_t plusNum);
		void ChangePlusLuck(const int32_t plusNum);
		void ChangePlusHeal(const int32_t plusNum);

	private:

		class WallPanelDrawer : public BaseDrawer
		{
		public:
			void Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent);
		};

		class EffectFontDrawer : public BaseDrawer
		{
		public:
			void Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent, const size_t index);
		};

		struct Wall
		{
			WallPanelDrawer wall_;
			EffectFontDrawer effect_;
			CountDrawer counter_;
		};
	
	private:

		std::array<Wall, 4> walls_;

	};
}
