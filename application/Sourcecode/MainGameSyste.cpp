#include "MainGameSyste.h"

MainGameSyste::MainGameSyste()
{
	panel_ = std::make_unique<Panel>();

	nowTurn_ = Turn::PLAYER;
	//�^�[�����Ƃɕ�[����~�m�̐�
	reloadMinoNum_ = 2;
}

void MainGameSyste::Update()
{
	panel_->Update();
}

void MainGameSyste::DrawSprite()
{
	panel_->DrawSprite();
}
