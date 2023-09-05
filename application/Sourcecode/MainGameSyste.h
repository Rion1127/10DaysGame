#pragma once
#include "Panel.h"
#include "Mino.h"
class MainGameSyste
{
private:
	enum class Turn {
		PLAYER,
		ENEMY
	};
private:
	Turn nowTurn_;

	std::unique_ptr<Panel> panel_;
	uint32_t reloadMinoNum_;
	std::vector<Mino> minos_;
public:
	MainGameSyste();
	void Update();
	void DrawSprite();
};

