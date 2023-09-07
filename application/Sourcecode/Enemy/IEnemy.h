#pragma once
#include "EnemyDrawer.h"

class IEnemy
{
protected:
	int32_t health_;
	bool isAlive_;
	int32_t attackPower_;
	
	// トランスフォーム
	YGame::YTransform trfm_;

	// アニメーション
	YGame::EnemyDrawer drawer_;
public:
	IEnemy();
	IEnemy(int32_t health, int32_t attackPower);
	virtual ~IEnemy() {
		int a = 0;
	};
	virtual void Update() = 0;
	virtual void Draw() = 0;

	virtual void DrawImGui() = 0;
public:
	void Damage(int32_t health);
public:
	bool GetIsAlive() { return isAlive_; }
	int32_t GetAttackPower() { return attackPower_; }
};

