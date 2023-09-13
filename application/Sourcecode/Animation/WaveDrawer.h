#pragma once
#include "CountDrawer.h"

namespace YGame
{
	class WaveDrawer
	{
		
	public:

		void Initialize();
		
		void GoNextWave();
		
		void Update();
		
		void Draw();
	
	private:

		class WaveFontDrawer : public BaseDrawer
		{
		public:
			void Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent);
		};

	private:

		YTransform trfm_;

		WaveFontDrawer fontDra_;
		CountDrawer counter_;

		bool isCount_ = false;
		YMath::YPower countPow_;
		YMath::YTimer dispTim_;
		YMath::Ease<float> countPos_;
		YMath::Ease<float> countScale_;
	};
}
