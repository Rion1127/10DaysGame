#pragma once
#include "BaseDrawer.h"

namespace YGame
{
	class TitleDrawer
	{
	
	public:

		void Initialize();

		void Update();
		
		void Draw();
	
	private:

		class BackDrawer : public BaseDrawer
		{
		public:
			void Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent);
		};

		class TitleLogoDrawer : public BaseDrawer
		{
		public:
			void Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent);
		};

		class CloudDrawer : public BaseDrawer
		{
		public:
			void Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent, const size_t texIndex);
		};

	private:

		BackDrawer back_;
		
		TitleLogoDrawer logo_;

		std::array<CloudDrawer, 2> clouds_;
	};
}
