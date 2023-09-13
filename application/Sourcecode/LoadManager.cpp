#include "LoadManager.h"


void LoadManager::LoadAllResources()
{
	LoadTexture();
	LoadModel();
	LoadSound();
}

void LoadManager::LoadModel()
{
}

void LoadManager::LoadTexture()
{
	LoadGraph("white1280x720.png", "White1280x720");
	LoadGraph("white1x1.png", "White");
	LoadGraph("number.png", "Number");
	//タイトル
	LoadGraph("title.png", "Title");
	LoadGraph("titleLogo.png", "TitleLogo");
	LoadGraph("cloud.png", "Cloud1");
	LoadGraph("cloud2.png", "Cloud2");
	//ステージセレクト
	LoadGraph("kanban.png", "KanBan");
	//ステージ背景
	LoadGraph("stagedodai.png", "Stage1");
	//パズル背景
	LoadGraph("sand.png", "Sand");
	LoadGraph("puzzleBackGround.png", "BackGroundSand");
	//パネル関連
	LoadGraph("panel.png", "Panel");
	LoadGraph("light.png", "Light");
	LoadGraph("nextPartsFrame.png", "Frame");
	LoadGraph("next.png", "Next");
	LoadGraph("lock.png", "Lock");
	LoadGraph("wall.png", "Wall");
	LoadGraph("effects.png", "Effect");
	//プレイヤー
	LoadGraph("player.png", "Player");
	LoadGraph("playerMove.png", "PlayerMove");
	//敵
	LoadGraph("slime.png", "Slime");
	LoadGraph("bat.png", "Bat");
	LoadGraph("blackBear.png", "Bear");
	//ボタンUI
	LoadGraph("beginner.png", "TutorialButton");
	LoadGraph("titleButton.png", "TitleButton");
	LoadGraph("endressRainbow.png", "EndlessButton");
	LoadGraph("retry.png", "Retry");
	LoadGraph("minoCouintUp.png", "MinoCouintUp");
	LoadGraph("mouse.png", "Mouse");
	LoadGraph("attackButton.png", "AttackButton");
	LoadGraph("pauseButton.png", "PauseButton");
	LoadGraph("pause.png", "Pause");
	LoadGraph("backButton.png", "BackButton");
	LoadGraph("redoButton.png", "RedoButton");
	LoadGraph("enemyStateUI.png", "EnemyStateUI");

	LoadGraph("yesButton.png", "YesButton");
	LoadGraph("noButton.png", "NoButton");
	LoadGraph("gameStartButtonAnime.png", "StartButton");


	//UI
	LoadGraph("textFrame.png", "TextFrame");
	LoadGraph("tutorialText.png", "TutorialText");
	LoadGraph("wave.png", "Wave");
	LoadGraph("statusFrame.png", "StatusFrame");
	LoadGraph("enemyStateUI.png", "EnemyStatusFrame");
	LoadGraph("longSword.png", "Sword");
	LoadGraph("critical.png", "CriticalFont");
	LoadGraph("criticalEffect.png", "CriticalEffect");
	
	LoadGraph("recoveryEffect.png", "Recovery");
	LoadGraph("debri.png", "Debri");
	LoadGraph("gameOver.png", "GameOver");
	LoadGraph("questClear.png", "QuestClear");
	LoadGraph("click.png", "Click");
	LoadGraph("story.png", "Story");
	LoadGraph("loading.png", "Load");
}

void LoadManager::LoadSound()
{
	LoadWave("attackSE.wav", "Attack");
	LoadWave("click_1SE.wav", "Click_1SE");
	LoadWave("click_2SE.wav", "Click_2SE");
	LoadWave("rotSE.wav", "RotSE");
	LoadWave("setSE.wav", "SetSE");
	LoadWave("cantSetSE.wav", "CantSetSE");
	LoadWave("statusUpSE.wav", "StatysUpSE");
	LoadWave("redoSE.wav", "RedoSE");
	LoadWave("unlockSE.wav", "UnlockSE");
	LoadWave("criticalSE.wav", "CriticalSE");
	LoadWave("recoverySE.wav", "RecoverySE");


	LoadWave("gameOverBGM.wav", "GameOverBGM");
	LoadWave("fightBGM.wav", "FightBGM");
	LoadWave("titleBGM.wav", "TitleBGM");
	LoadWave("clearBGM.wav", "ClearBGM");
}
