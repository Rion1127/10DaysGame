#pragma once
#include "Panel.h"
#include "Mino.h"
#include "Player.h"
#include "IEnemy.h"
class MainGameSyste
{
private:
	enum class Turn {
		PLAYER,
		ENEMY,
		CHANGE
	};
private:
	//現在のターン
	Turn nowTurn_;
	//ひとつ前のターン
	Turn prevTurn_;

	std::unique_ptr<Panel> panel_;
	uint32_t reloadMinoNum_;
	std::vector<Mino> minos_;

	Player* player_;
	IEnemy* enemy_;
public:
	MainGameSyste();
	void Update();
	void DrawSprite();
	void DrawImGui();
public:
	void SetPlayer(Player* player) { player_ = player; }
	void SetEnemy(IEnemy* enemy) { enemy_ = enemy; }
};

