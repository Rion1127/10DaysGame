#pragma once
#include "BaseDrawer.h"
#include "SlimeActor.h"
#include "Ease.h"

namespace YGame
{
	class SwordDrawer
	{

	public:

		/// <summary>
		/// ������
		/// </summary>
		/// <param name="maxXSize"> : X���ő�l</param>
		/// <param name="maxYSize"> : Y���ő�l</param>
		/// <param name="matParent"> : �e�s��</param>
		void Initialize(const size_t maxXSize, const size_t maxYSize, Matrix4* matParent);

		/// <summary>
		/// �U���A�j���[�V����
		/// </summary>
		/// <param name="panelIndices"> : �p�l���ԍ�</param>
		void AttackAnimation(const std::vector<std::vector<int32_t>>& panelIndices);

		/// <summary>
		/// �X�V
		/// </summary>
		void Update();

		/// <summary>
		/// �`��
		/// </summary>
		void Draw();

	private:

		// �U���A�j���[�V�����X�V
		void UpdateAttackAnimation(YGame::YTransform::Status& animeStatus);

		// �F�A�j���[�V�����X�V
		void UpdateColorAnimation();

	private:

		// ������
		class HandleDrawer final : public BaseDrawer 
		{
		
		public:

			void Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent);

			void SetAlpha(const float alpha);
		};

		// �p�l��
		class PanelDrawer final : public BaseDrawer 
		{

		public:

			void Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent);

			void InitializeAnime(const int32_t panelIndex, const YTransform::Status& trfmStatus);

			void StrikeAnimation(const Vector3& upDir);

			void UpdateAnimation() override;

			void SetAlpha(const float alpha);
		
		private:

			int32_t index_;

			bool isUpdate_ = false;
			Vector3 upDir_;

			Vector3 moveSpeed_;
			Vector3 rotaSpeed_;
			Vector3 scaleSpeed_;
		};

		// �U���i�K
		enum class AttackStep
		{
			None, Forge, Slash, Strike,
		};

	private:

		YTransform trfm_;

		// ������
		HandleDrawer handle_;

		// �p�l��
		std::vector<std::vector<PanelDrawer>> panels_;

		// �X���C���A�j���[�V�����p
		YGame::SlimeActor slime_;

		// �A�j���[�V�����p
		YMath::Ease<float> rotaEas_;
		YMath::YTimer rotaTim_;

		YMath::YPower alphaPow_;

		float panelCounter_ = 0.0f;

		YMath::YTimer breakTim_;

		AttackStep step_ = AttackStep::None;
	};
}