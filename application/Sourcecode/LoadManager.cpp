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
	//�v���C���[
	LoadGraph("player.png", "Player");
	LoadGraph("playerMove.png", "PlayerMove");
	//�G
	LoadGraph("slime.png", "Enemy");
	//�{�^��UI
	LoadGraph("gameStartButton.png", "GameStartButton");
	LoadGraph("tutorialButton.png", "TutorialButton");
	LoadGraph("titleButton.png", "TitleButton");
	LoadGraph("endlessButton.png", "EndlessButton");
	LoadGraph("dotTest.png", "DotTest");
	LoadGraph("retry.png", "Retry");
	LoadGraph("minoCouintUp.png", "MinoCouintUp");
	LoadGraph("mouse.png", "Mouse");
	LoadGraph("attackButton.png", "AttackButton");
	LoadGraph("pauseButton.png", "PauseButton");
	LoadGraph("pause.png", "Pause");
	LoadGraph("backButton.png", "BackButton");
	LoadGraph("redoButton.png", "RedoButton");
	//UI
	LoadGraph("textFrame.png", "TextFrame");
	LoadGraph("tutorialText.png", "TutorialText");
	LoadGraph("statusFrame.png", "StatusFrame");
	LoadGraph("sword.png", "Sword");
	
	LoadGraph("recoveryEffect.png", "Recovery");
	LoadGraph("debri.png", "Debri");
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
}
