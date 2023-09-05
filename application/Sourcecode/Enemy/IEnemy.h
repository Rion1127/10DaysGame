#pragma once
#include "Vector2.h"
#include "Sprite.h"

#include "YTransform.h"
#include "HitActor.h"

class IEnemy
{
protected:
	// トランスフォーム
	YGame::YTransform trfm_;
	// 被弾アニメーション
	YGame::HitActor hitActor_;

	std::unique_ptr<Sprite> sprite_ = nullptr;

	int32_t health_;
	bool isAlive_;
	int32_t attackPower_;
public:
	IEnemy();
	IEnemy(int32_t health, int32_t attackPower);
	virtual void Update() = 0;
	virtual void Draw() = 0;

	virtual void DrawImGui() = 0;
public:
	void Damage(int32_t health);
public:
	bool GetIsAlive() { return isAlive_; }
	int32_t GetAttackPower() { return attackPower_; }
};

