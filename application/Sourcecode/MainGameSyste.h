#pragma once
#include "Panel.h"
#include "Player.h"
#include "IEnemy.h"
#include "EnemyManager.h"
#include "YCameraManager.h"
#include "NextMinoDrawer.h"
#include "WallDrawer.h"
#include "Button.h"
#include "Timer.h"
#include "GameOverEffect.h"
#include "ClearEffect.h"
#include "StoryText.h"
#include "WaveDrawer.h"

#include "MouseUI.h"
class MainGameSyste
{
private:
	enum class Turn {
		PLAYER,
		ENEMY,
		CHANGE
	};
public:
	enum class State {
		GAME,
		CLEAR,
		GAMEOVER,
		PAUSE
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
	
	YGame::NextMinoDrawer nextMinoDrawer_;
	YGame::WallDrawer wallDrawer_;
	YGame::WaveDrawer waveDrawer_;

	Player* player_;
	IEnemy* enemy_;

	EnemyManager enemyManager_;
	
	// カメラ
	YGame::YCameraManager* cameraManager_;

	std::unique_ptr<Button> titleButton_;
	std::unique_ptr<Button> retryButton_;
	Vector2 uiUpPos_;
	Vector2 uiDownPos_;

	std::unique_ptr<Button> attackButton_;
	Vector2 attackPos_;

	MouseUI mouseUi_;

	std::unique_ptr<Button> pauseButton_;
	std::unique_ptr<Button> backButton_;
	Vector2 pausePos_;
	Vector2 backPos_;
	std::unique_ptr<Sprite> backSprite_;
	std::unique_ptr<Sprite> pauseSprite_;
	bool isNext_;

	std::unique_ptr<Sprite> swordSprite_;
	std::unique_ptr<Button> redoButton_;
	Vector2 redoPos_;

	GameOverEffect gameOverEffect_;
	ClearEffect clearEffect_;
	StoryText storyText_;
public:
	MainGameSyste();
	void Update();
	void DrawSprite();
	void DrawSpriteFront();
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
	
	void MinoCountUp();
public:
	void SetPlayer(Player* player) { 
		player_ = player;
		enemyManager_.SetPlayer(player);
	}
	void SetEnemy(IEnemy* enemy) { enemy_ = enemy; }
public:
	State GetGameState() { return gameState_; }
private:
	enum class TutorialStep {
		Set,
		Rot,
		StatusUp,
		PanelNumUp,
		End
	};
private:
	TutorialStep tutorialstep_;

	int32_t tutorialIndexX_;
	int32_t oldTutorialIndexX_;
	int32_t tutorialIndexY_;

	std::unique_ptr<Sprite> textFrameSprite_;
	std::unique_ptr<Sprite> textSprite_;
public:
	void TutorialInit();
	void TutorialUpdate();
	void TutorialDraw();
	void TutorialDrawFront();
	void TutorialDrawImGui();
};

