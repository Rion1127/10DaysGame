#pragma once
#include "PlayerDrawer.h"
#include "SwordDrawer.h"
#include "GaugeDrawer.h"
#include "DamageDrawer.h"
#include "RecoveryDrawer.h"
#include "StatusDrawer.h"

class Player
{
private:
	int32_t health_;		//�̗�
	int32_t luck_;			//�^
	int32_t guard_;	//�h���
	int32_t baseAttackpower_;//�U����
	bool isAlive_;

	// �g�����X�t�H�[��
	YGame::YTransform trfm_;

	// �A�j���[�V����
	YGame::PlayerDrawer drawer_;
	YGame::SwordDrawer sword_;
	YGame::GaugeDrawer hpBar_;
	YGame::DamageDrawer damage_;
	YGame::RecoveryDrawer recovery_;
	
	YGame::YTransform statusTrfm_;
	std::array<YGame::StatusDrawer, 4> status_;
	Sprite statusFrame_;
public:

	void Initialize();

	void Update();

	void AttackAnimation(const std::vector<std::vector<int32_t>>& panelIndices);
	void IdleAnimation();
	void MoveAnimation();

	void Draw();
	void DrawImGui();
public:
	void Damage(int32_t damage, const bool isCritical = false);
	
	void Recovery(int32_t recover);
	void AddGurd(int32_t gurd);
	void AddAttack(int32_t attack);
	void AddLuck(int32_t luck);
public:
	int32_t GetAttackPower() { return baseAttackpower_; }
	int32_t GetGuard() { return guard_; }
	bool GetIsAlive() { return isAlive_; }
	bool GetRotTimEnd() { return sword_.GetRotaTimEnd(); }
};

