#pragma once
#include "YTransform.h"
#include "SlimeActor.h"
#include "Sprite.h"
#include "Ease.h"

class Sword
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

	void UpdateColorAnimation();

private:

	// ������
	struct Handle
	{
		YGame::YTransform trfm_;
		Sprite sprite_;
	};
	
	// �p�l��
	struct Panel
	{
		int32_t index_;
		YGame::YTransform trfm_;
		Sprite sprite_;
		
		YGame::YTransform::Status breakStatus_;
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

	// �e�g�����X�t�H�[��
	YGame::YTransform trfm_;

	// ������
	Handle handle_;
	
	// �p�l��
	std::vector<std::vector<Panel>> panels_;


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

