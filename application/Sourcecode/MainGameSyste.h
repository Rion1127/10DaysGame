#pragma once
#include "Panel.h"
#include "Mino.h"
#include "Player.h"
#include "IEnemy.h"
#include "EnemyManager.h"
#include "YCameraManager.h"
#include "Button.h"
class MainGameSyste
{
private:
	enum class Turn {
		PLAYER,
		ENEMY,
		CHANGE
	};
	enum class State {
		GAME,
		CLEAR,
		GAMEOVER
	};
private:
	//現在のターン
	Turn nowTurn_;
	//ひとつ前のターン
	Turn prevTurn_;
	State gameState_;

	std::unique_ptr<Panel> panel_;
	uint32_t reloadMinoNum_;
	std::vector<MinoType> minos_;
	std::vector<MinoType> minosList_;
	std::vector<int32_t> powerUpCost_;
	std::vector<int32_t> minoCountUpCost_;
	uint32_t powerLevel_;
	uint32_t minoCountLevel_;

	Player* player_;
	IEnemy* enemy_;

	EnemyManager enemyManager_;
	
	// カメラ
	YGame::YCameraManager* cameraManager_;

	std::unique_ptr<Button> titleButton_;
	std::unique_ptr<Button> retryButton_;
	Vector2 uiUpPos_;
	Vector2 uiDownPos_;

	std::unique_ptr<Button> powerUpButton_;
	std::unique_ptr<Button> minoCountUpButton_;
	Vector2 powerUpPos_;
	Vector2 minoCountUpPos_;
public:
	MainGameSyste();
	void Update();
	void DrawSprite();
	void DrawImGui();
private:
	void SpriteInit();
	void CostInit();
	//ミノを補充する
	void ReloadMino();

	void TurnChange();
	void TurnPlayer();
	void TurnEnemy();

	void GameOverUpdate();
	void PowerUp();
	void MinoCountUp();
public:
	void SetPlayer(Player* player) { player_ = player; }
	void SetEnemy(IEnemy* enemy) { enemy_ = enemy; }
};

