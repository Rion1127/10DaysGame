#pragma once
#include "BaseDrawer.h"
#include "YTimer.h"

namespace YGame
{
	class TitleDrawer
	{
	
	public:

		void Initialize();

		void Update();
		
		void Draw();
	
	private:

		void EmitCloud();
	
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
			void EmitAnimation(const Vector3& pos, const float speed, const size_t texIndex);
			bool IsAlive() const { return isAlive_; }
		private:
			void ResetAnimation() override;
			void UpdateAnimation() override;
		private:
			bool isAlive_ = false;
			float speed_ = 0.0f;
		};

	private:

		BackDrawer back_;
		TitleLogoDrawer logo_;
		std::array<CloudDrawer, 20> clouds_;

		YMath::YTimer emitTimer_;

	};
}
