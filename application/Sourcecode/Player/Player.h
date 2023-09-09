#pragma once
#include "PlayerDrawer.h"
#include "SwordDrawer.h"
#include "HPDrawer.h"
#include "DamageDrawer.h"

class Player
{
private:
	int32_t health_;
	int32_t attackpower_;
	int32_t baseAttackpower_;
	int32_t powerUpValue_;
	bool isAlive_;

	// トランスフォーム
	YGame::YTransform trfm_;

	// アニメーション
	YGame::PlayerDrawer drawer_;
	YGame::SwordDrawer sword_;
	YGame::HPDrawer hpBar_;
	YGame::DamageDrawer damage_;
public:

	void Initialize();

	void Update();

	void AttackAnimation(const std::vector<std::vector<int32_t>>& panelIndices);
	void IdleAnimation();
	void MoveAnimation();

	void AddPowerReset() { powerUpValue_ = 0; };

	void Draw();
	void DrawImGui();
public:
	void Damage(int32_t damage);
	void SetAttackPower(int32_t power) { attackpower_ = power; }
	void AddAttackPower(int32_t power) { powerUpValue_ = power; }
	void Recovery(int32_t health);
public:
	int32_t GetAttackPower() { return attackpower_; }
	bool GetIsAlive() { return isAlive_; }
	bool GetRotTimEnd() { return sword_.GetRotaTimEnd(); }
};

