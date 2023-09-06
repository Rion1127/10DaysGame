#pragma once
#include "PlayerDrawer.h"
#include "SwordDrawer.h"

class Player
{

public:

	void Initialize();

	void Update();

	void AttackAnimation(const std::vector<std::vector<int32_t>>& panelIndices);

	void Draw();
	void DrawImGui();
public:
	void Damage(int32_t damage);
public:
	int32_t GetAttackPower() { return attackpower_; }
private:
	int32_t health_;
	int32_t attackpower_;

	// �g�����X�t�H�[��
	YGame::YTransform trfm_;
	
	// �A�j���[�V����
	YGame::PlayerDrawer drawer_;
	YGame::SwordDrawer sword_;
};

