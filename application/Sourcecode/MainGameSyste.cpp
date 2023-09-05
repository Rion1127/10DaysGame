#include "MainGameSyste.h"
#include "RRandom.h"

MainGameSyste::MainGameSyste()
{
	panel_ = std::make_unique<Panel>();

	nowTurn_ = Turn::PLAYER;
	//�^�[�����Ƃɕ�[����~�m�̐�
	reloadMinoNum_ = 2;

	ReloadMino();

	enemy_ = enemyManager_.GetNowEnemy();

	// �J�����擾 + ������
	cameraManager_ = YCameraManager::GetInstance();
	cameraManager_->Initialize();
}

void MainGameSyste::Update()
{
	enemyManager_.Update();
	if (enemyManager_.GetIsAllEnemyDestroy() == false) {
		panel_->Update();

		//�G�̍U��
		if (nowTurn_ == Turn::PLAYER) {
			TurnPlayer();
		}
		//�G�̍U��
		else if (nowTurn_ == Turn::ENEMY) {
			TurnEnemy();
		}
		//�^�[������シ��
		else if (nowTurn_ == Turn::CHANGE) {
			//�^�[�����`�F���W����
			TurnChange();
		}

		//�O�̃^�[�����ǂ����̃^�[�����L�^���Ă���
		if (nowTurn_ != Turn::CHANGE) {
			prevTurn_ = nowTurn_;
		}
	}
	//�N���A������
	else {

	}

	

	if (enemyManager_.GetIsChangeNowEnemy()) {
		enemy_ = enemyManager_.GetNowEnemy();
		enemyManager_.SetIsChangeNowEnemy(false);
	}

	// �J�����X�V
	cameraManager_->Update();
}

void MainGameSyste::DrawSprite()
{
	panel_->DrawSprite();
	enemyManager_.Draw();
}

void MainGameSyste::DrawImGui()
{
	if (enemy_ != nullptr) {
		enemy_->DrawImGui();
	}
	panel_->DrawImGui();
	ImGui::Begin("MainGameSyste");
	ImGui::Text("%d", reloadMinoNum_);

	std::string string = "NowTurn : ";

	if (nowTurn_ == Turn::PLAYER)string += "PLAYER";
	if (nowTurn_ == Turn::CHANGE)string += "CHANGE";
	if (nowTurn_ == Turn::ENEMY)string += "ENEMY";

	ImGui::Text(string.c_str());

	std::string gameStatestring = "GameState : ";

	if (enemyManager_.GetIsAllEnemyDestroy())gameStatestring += "Clear";
	else gameStatestring += "fighting";

	ImGui::Text(gameStatestring.c_str());

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
	//�����̃^�[����������G�̃^�[����
	if (prevTurn_ == Turn::PLAYER) {
		nowTurn_ = Turn::ENEMY;
	}
	//�G�̃^�[���������玩���̃^�[����
	else if (prevTurn_ == Turn::ENEMY) {
		nowTurn_ = Turn::PLAYER;
		//�~�m�������[�h����
		ReloadMino();
	}
	prevTurn_ = nowTurn_;
}

void MainGameSyste::TurnPlayer()
{
	if (minos_.size() > 0) {
		panel_->SetMinoType(minos_[0]);
	}

	//�p�l���̐ݒu������������
	if (panel_->GetisSetComplete()) {
		panel_->SetisSetComplete(false);
		//�z�u�o�����~�m������
		minos_.erase(minos_.begin());

		//�c��̐���0�ɂȂ����ꍇ�^�[�����I������
		if (minos_.size() <= 0) {
			//�p�l���X�V
			panel_->PanelUpdate();
			reloadMinoNum_ = 2;
			//�G�Ƀ_���[�W��^����
			int32_t damage = panel_->GetAttackPanelNum() * player_->GetAttackPower();
			enemy_->Damage(damage);
			nowTurn_ = Turn::CHANGE;

			player_->AttackAnimation(panel_->GetDisplayPanel());
		}
	}
}

void MainGameSyste::TurnEnemy()
{
	//�v���C���[���_���[�W���󂯂�
	if (enemyManager_.GetIsChangeNowEnemy() == false) {
		player_->Damage(enemy_->GetAttackPower());
	}

	//�������I�������V�[�����`�F���W����
	nowTurn_ = Turn::CHANGE;
}
