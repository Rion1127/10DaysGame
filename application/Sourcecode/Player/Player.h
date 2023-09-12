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
	int32_t health_;		//体力
	int32_t luck_;			//運
	int32_t guard_;	//防御力
	int32_t baseAttackpower_;//攻撃力
	bool isAlive_;

	// トランスフォーム
	YGame::YTransform trfm_;

	// アニメーション
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

