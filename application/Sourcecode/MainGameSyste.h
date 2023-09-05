#pragma once
#include "Panel.h"
#include "Mino.h"
#include "Player.h"
#include "IEnemy.h"
#include "EnemyManager.h"
class MainGameSyste
{
private:
	enum class Turn {
		PLAYER,
		ENEMY,
		CHANGE
	};
private:
	//���݂̃^�[��
	Turn nowTurn_;
	//�ЂƂO�̃^�[��
	Turn prevTurn_;

	std::unique_ptr<Panel> panel_;
	uint32_t reloadMinoNum_;
	std::vector<MinoType> minos_;
	std::vector<MinoType> minosList_;

	Player* player_;
	IEnemy* enemy_;

	EnemyManager enemyManager_;
public:
	MainGameSyste();
	void Update();
	void DrawSprite();
	void DrawImGui();
private:
	//�~�m���[����
	void ReloadMino();

	void TurnChange();
	void TurnPlayer();
	void TurnEnemy();
public:
	void SetPlayer(Player* player) { player_ = player; }
	void SetEnemy(IEnemy* enemy) { enemy_ = enemy; }
};

