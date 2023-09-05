#pragma once
#include "Sword.h"

class Player
{

public:

	void Initialize();

	void Update();

	void AttackAnimation(const std::vector<std::vector<int32_t>>& panelIndices);

	void Draw();
	void DrawImGui();
public:
	void Damage(int32_t damage) { health_ -= damage; }
public:
	int32_t GetAttackPower() { return attackpower_; }
private:
	YGame::YTransform trfm_;

	std::unique_ptr<Sprite> sprite_ = nullptr;
	int32_t health_;
	int32_t attackpower_;

	Sword sword_;
};

