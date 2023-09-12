#pragma once
#include "EnemyDrawer.h"
#include "GaugeDrawer.h"
#include "DamageDrawer.h"

class IEnemy
{
protected:
	int32_t health_;
	bool isAlive_;
	int32_t attackPower_;
	int32_t guard_;
	
	// トランスフォーム
	YGame::YTransform trfm_;

	// アニメーション
	YGame::EnemyDrawer drawer_;
	YGame::GaugeDrawer hpBar_;
	YGame::DamageDrawer damage_;
public:
	IEnemy();
	IEnemy(int32_t health, int32_t attackPower);
	virtual ~IEnemy() {
		int a = 0;
	};
	virtual void Update() = 0;
	virtual void Draw() = 0;

	virtual void DrawImGui() = 0;

	void AttackAnimation();
public:
	void Damage(int32_t health);
public:
	bool GetIsAlive() { return isAlive_; }
	int32_t GetAttackPower() { return attackPower_; }
	int32_t GetGuard() { return guard_; }
	bool GetIsEndAttack() { return drawer_.GetIsEndAttack(); }
};

