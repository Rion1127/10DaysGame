#pragma once
#include "Mino.h"
#include "BlockDrawer.h"
#include "GaugeDrawer.h"

namespace YGame
{
	class NextMinoDrawer
	{
	
	public:
	
		/// <summary>
		/// ������
		/// </summary>
		void Initialize();
		
		/// <summary>
		/// �X�V
		/// </summary>
		void Update(const int32_t minoCount);

		/// <summary>
		/// �`��
		/// </summary>
		void Draw();

		/// <summary>
		/// ���������A�j���[�V����
		/// </summary>
		/// <param name="minos"> : ���̃~�m�̏��</param>
		void RedrawAnimation(const std::vector<MinoType>& minos);

		/// <summary>
		/// ���b�N�����A�j���[�V����
		/// </summary>
		void UnlockAnimiation();

		/// <summary>
		/// �i�ރA�j���[�V����
		/// </summary>
		/// <param name="minos"> : ���̃~�m�̏��</param>
		void AdvanceAnimation(const std::vector<MinoType>& minos);

		/// <summary>
		/// �ނ��A�j���[�V����
		/// </summary>
		/// <param name="minos"> : ���̃~�m�̏��</param>
		void RetreatAnimation(const std::vector<MinoType>& minos);
	
	private:
		
		YTransform::Status AnimeStatus(const size_t index);

		void ChangeNextMino();
	
	private:

		class FrameDrawer : public BaseDrawer
		{
		public:
			void Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent);
		};
		
		class LockDrawer : public BaseDrawer
		{
		public:
			void Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent);
		};
		
		class NextDrawer : public BaseDrawer
		{
		public:
			void Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent);
		};

		struct Lock
		{
			LockDrawer lock_;
			BlockDrawer block_;
			GaugeDrawer gauge_;
		};
		
		class NextFrameDrawer
		{

		public:

			void Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent);
			void Update(const YTransform::Status& animeStatus = {});
			void Draw();

			void ResetAnimation();
			void SetIsExist(const bool isExist) { isExist_ = isExist; }
			
			void ChangeMino(const MinoType type);
			void ChangeVoid();
			void ChangeRock(Lock* pLock);

		private:

			YTransform trfm_;

			std::array<BlockDrawer, 4> drawers_;
			FrameDrawer frame_;
			Lock* pLock_ = nullptr;

			bool isExist_ = false;
			YMath::YPower existPow_;
			YMath::Ease<Vector3> existScaleEas_;
		};
		
	private:

		std::vector<MinoType> minos_;

		std::array<NextFrameDrawer, 6> nexts_;

		NextDrawer nextDra_;

		Lock lock_;
		
		bool isReset_ = false;
		YMath::YTimer resetTimer_;

		bool isAdvence_ = false;
		bool isRetreat_ = false;
		YMath::YTimer riseTimer_;

		bool isUnlock_ = false;
		YMath::YPower unlockPower_;
		YMath::Ease<float> unlockHeightEas_;
		YMath::Ease<float> unlockRotaEas_;		
	};
}
