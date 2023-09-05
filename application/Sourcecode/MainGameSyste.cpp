#include "MainGameSyste.h"
#include "RRandom.h"

MainGameSyste::MainGameSyste()
{
	panel_ = std::make_unique<Panel>();

	nowTurn_ = Turn::PLAYER;
	//�^�[�����Ƃɕ�[����~�m�̐�
	reloadMinoNum_ = 2;

	ReloadMino();
}

void MainGameSyste::Update()
{
	panel_->Update();
	//�p�l���̐ݒu������������
	if (panel_->GetisSetComplete()) {
		panel_->SetisSetComplete(false);
		//�z�u�o������~�m������
		minos_.erase(minos_.begin());
		
		//�c��̐���0�ɂȂ����ꍇ�^�[�����I������
		if (minos_.size() <= 0) {
			//�v���C���[�^�[���I�����o�͂�����


			nowTurn_ = Turn::CHANGE;
		}
	}

	//�G�̍U��
	if (nowTurn_ == Turn::PLAYER) {
		if (minos_.size() > 0) {
			panel_->SetMinoType(minos_[0]);
		}
	}
	//�G�̍U��
	else if (nowTurn_ == Turn::ENEMY) {
		//�v���C���[���_���[�W���󂯂�
		if (enemy_->GetIsAlive()) {
			player_->Damage(enemy_->GetAttackPower());
		}
		//�G�l�~�[�^�[���I�����o�͂�����

		//�������I�������V�[�����`�F���W����
		nowTurn_ = Turn::CHANGE;
	}
	//�^�[�����`�F���W����
	TurnChange();
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

void MainGameSyste::ReloadMino()
{
	minos_.clear();
	for (uint32_t i = 0; i < reloadMinoNum_; i++) {
		//�~�m���X�g�ɖ����Ƃ��ɕ�[����
		if (minosList_.size() == 0) {
			for (uint32_t i = 0; i < 7; i++) {
				minosList_.push_back((MinoType)i);
			}
		}

		int32_t max = (int32_t)minosList_.size() - 1;
		int32_t rand = RRandom::Rand(0, max);

		minos_.push_back(minosList_[rand]);
		minosList_.erase(minosList_.begin() + rand);
	}

}

void MainGameSyste::TurnChange()
{
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
			//�~�m�������[�h����
			ReloadMino();
		}
		prevTurn_ = nowTurn_;
	}
	//�O�̃^�[�����ǂ����̃^�[�����L�^���Ă���
	else {
		prevTurn_ = nowTurn_;
	}

}
