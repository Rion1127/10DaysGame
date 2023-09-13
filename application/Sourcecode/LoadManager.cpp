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
	//�^�C�g��
	LoadGraph("karititledot0912.png", "Title");
	LoadGraph("titleLogo.png", "TitleLogo");
	LoadGraph("cloud.png", "Cloud1");
	LoadGraph("cloud2.png", "Cloud2");
	//�X�e�[�W�Z���N�g
	LoadGraph("kanban.png", "KanBan");
	//�X�e�[�W�w�i
	LoadGraph("stagedodai.png", "Stage1");
	//�p�Y���w�i
	LoadGraph("sand.png", "Sand");
	LoadGraph("puzzleBackGround.png", "Sand1");
	//�p�l���֘A
	LoadGraph("panel.png", "Panel");
	LoadGraph("powerUpPanel.png", "PowerUpPanel");
	LoadGraph("recoveryPanel.png", "RecoveryPanel");
	LoadGraph("light.png", "Light");
	LoadGraph("nextPartsFrame.png", "Frame");
	LoadGraph("next.png", "Next");
	LoadGraph("lock.png", "Lock");
	LoadGraph("wall.png", "Wall");
	LoadGraph("effects.png", "Effect");
	//�v���C���[
	LoadGraph("player.png", "Player");
	LoadGraph("playerMove.png", "PlayerMove");
	//�G
	LoadGraph("slime.png", "Slime");
	LoadGraph("bat.png", "Bat");
	LoadGraph("blackBear.png", "Bear");
	//�{�^��UI
	LoadGraph("gameStartButton.png", "GameStartButton");
	LoadGraph("beginner.png", "TutorialButton");
	LoadGraph("titleButton.png", "TitleButton");
	LoadGraph("endressRainbow.png", "EndlessButton");
	LoadGraph("dotTest.png", "DotTest");
	LoadGraph("retry.png", "Retry");
	LoadGraph("minoCouintUp.png", "MinoCouintUp");
	LoadGraph("mouse.png", "Mouse");
	LoadGraph("attackButton.png", "AttackButton");
	LoadGraph("pauseButton.png", "PauseButton");
	LoadGraph("pause.png", "Pause");
	LoadGraph("backButton.png", "BackButton");
	LoadGraph("redoButton.png", "RedoButton");
	LoadGraph("enemyStateUI.png", "EnemyStateUI");
	LoadGraph("gameStartButtonAnime.png", "StartButton1");


	//UI
	LoadGraph("textFrame.png", "TextFrame");
	LoadGraph("tutorialText.png", "TutorialText");
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
