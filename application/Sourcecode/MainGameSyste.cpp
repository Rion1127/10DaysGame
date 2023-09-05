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
	//�p�l���̐ݒu������������
	if (panel_->GetisSetComplete()) {
		panel_->SetisSetComplete(false);

		reloadMinoNum_--;
		//�c��̐���0�ɂȂ����ꍇ�^�[�����I������
		if (reloadMinoNum_ <= 0) {
			//�v���C���[�^�[���I�����o�͂�����


			nowTurn_ = Turn::CHANGE;
		}
	}

	//�G�̍U��
	if (nowTurn_ == Turn::ENEMY) {
		player_->Damage(10);
		//�G�l�~�[�^�[���I�����o�͂�����

		//�������I�������V�[�����`�F���W����
		nowTurn_ = Turn::CHANGE;
	}

	//�^�[������シ��
	if (nowTurn_ == Turn::CHANGE) {
		//�V�[���`�F���W���o�͂�����


		//�����̃^�[����������G�̃^�[����
		if (prevTurn_ == Turn::PLAYER) {
			nowTurn_ = Turn::ENEMY;

			//�p�l���X�V
			panel_->PanelUpdate();
			reloadMinoNum_ = 2;
			int32_t damage = panel_->GetAttackPanelNum() * player_->GetAttackPower();
			enemy_->Damage(damage);
		}
		//�G�̃^�[���������玩���̃^�[����
		else if (prevTurn_ == Turn::ENEMY) {
			nowTurn_ = Turn::PLAYER;
			
		}
		prevTurn_ = nowTurn_;
	}
	//�O�̃^�[�����ǂ����̃^�[�����L�^���Ă���
	else {
		prevTurn_ = nowTurn_;
	}
	
}

void MainGameSyste::DrawSprite()
{
	panel_->DrawSprite();
}

void MainGameSyste::DrawImGui()
{
	panel_->DrawImGui();
	ImGui::Begin("MainGameSyste");
	ImGui::Text("%d", reloadMinoNum_);

	std::string string = "NowTurn : ";

	if (nowTurn_ == Turn::PLAYER)string += "PLAYER";
	if (nowTurn_ == Turn::CHANGE)string += "CHANGE";
	if (nowTurn_ == Turn::ENEMY)string += "ENEMY";

	ImGui::Text(string.c_str());

	ImGui::End();
}
