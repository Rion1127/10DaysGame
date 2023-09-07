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
	//�p�l���֘A
	LoadGraph("panel.png", "Panel");
	//�v���C���[
	LoadGraph("player.png", "Player");
	LoadGraph("playerMove.png", "PlayerMove");
	//�G
	LoadGraph("enemy.png", "Enemy");
	//�{�^��UI
	LoadGraph("gameStartButton.png", "GameStartButton");
	LoadGraph("tutorialButton.png", "TutorialButton");
	LoadGraph("titleButton.png", "TitleButton");
	LoadGraph("endlessButton.png", "EndlessButton");
	LoadGraph("dotTest.png", "DotTest");
	LoadGraph("retry.png", "Retry");
	LoadGraph("minoCouintUp.png", "MinoCouintUp");
}

void LoadManager::LoadSound()
{
	LoadWave("swingSE.wav", "SwingSE");
	LoadWave("hitSE.wav", "HitSE");
	LoadWave("lockOnSE.wav", "lockOnSE");
	LoadWave("enterSE.wav", "EnterSE");
	LoadWave("selectSE.wav", "SelectSE");
	LoadWave("guardSE.wav", "GuardSE");
	LoadWave("guardHitSE.wav", "GuardHitSE");
	LoadWave("deathSE.wav", "DeathSE");
	LoadWave("shine.wav", "ShineSE");
}
