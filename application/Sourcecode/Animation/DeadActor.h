#pragma once
#include "BaseDrawer.h"
#include "YTimer.h"
#include "SplineEase.h"
#include "Ease.h"

namespace YGame
{
	class DeadActor
	{
	
	public:

		void Explosion(const Vector3& pos);
	
	public:

		DeadActor() = default;

		virtual ~DeadActor() = default;
	
	public:

		static void StaticInitialize();
		static void StaticUpdate();
		static void StaticDraw();

	private:

		class DebriDrawer : public BaseDrawer
		{
		public:
			void Initialize();
			void Emit(const Vector3& pos);
			bool IsAlive() const { return aliveTim_.IsAct(); }
		private:
			void UpdateAnimation() override;
		private:
			YMath::YTimer aliveTim_;
			YMath::SplineEase<Vector3> posEas_;
			YMath::Ease<float> rotaEas_;
			YMath::Ease<float> scaleEas_;
			Color color_;
		};
	
	private:

		static std::array<DebriDrawer, 100> sDebris_;
	
	};
}
