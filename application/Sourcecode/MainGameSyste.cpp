#include "MainGameSyste.h"
#include "RRandom.h"
#include "SceneManager.h"
#include "mSound.h"

using YGame::YCameraManager;

MainGameSyste::MainGameSyste()
{
	panel_ = std::make_unique<Panel>();

	nowTurn_ = Turn::PLAYER;
	gameState_ = State::GAME;
	//�^�[�����Ƃɕ�[����~�m�̐�
	reloadMinoNum_ = 4;

	ReloadMino();

	nextMinoDrawer_.Initialize();
	minoCounterDrawer_.Initialize();
	
	enemy_ = enemyManager_.GetNowEnemy();

	// �J�����擾 + ������
	cameraManager_ = YCameraManager::GetInstance();
	cameraManager_->Initialize();

	SpriteInit();
	CostInit();

	redoCoolTime_.SetLimitTime(5);
	isNext_ = false;

	tutorialstep_ = TutorialStep::Set;
}

void MainGameSyste::SpriteInit()
{
	uiUpPos_ = {
		WinAPI::GetWindowSize().x / 2.f,
		WinAPI::GetWindowSize().y / 1.8f
	};
	titleButton_ = std::make_unique<Button>(uiUpPos_);
	titleButton_->SetTexture(TextureManager::GetInstance()->GetTexture("TitleButton"));
	uiDownPos_ = {
		WinAPI::GetWindowSize().x / 2.f,
		WinAPI::GetWindowSize().y / 1.5f
	};
	retryButton_ = std::make_unique<Button>(uiUpPos_);
	retryButton_->SetTexture(TextureManager::GetInstance()->GetTexture("Retry"));

	attackPos_ = {
		80.f,
		300.f
	};
	attackButton_ = std::make_unique<Button>(attackPos_);
	attackButton_->SetTexture(TextureManager::GetInstance()->GetTexture("AttackButton"));

	pausePos_ = {
		80.f,
		50.f
	};
	pauseButton_ = std::make_unique<Button>(pausePos_);
	pauseButton_->SetTexture(TextureManager::GetInstance()->GetTexture("PauseButton"));

	backPos_ = uiDownPos_;
	backButton_ = std::make_unique<Button>(backPos_);
	backButton_->SetTexture(TextureManager::GetInstance()->GetTexture("BackButton"));
	backButton_->Update();

	pauseSprite_ = std::make_unique<Sprite>();
	pauseSprite_->Ini();
	pauseSprite_->SetTexture(TextureManager::GetInstance()->GetTexture("Pause"));
	Vector2 pausePos = {
		WinAPI::GetWindowSize().x / 2.f,
		WinAPI::GetWindowSize().y / 2.5f
	};
	pauseSprite_->SetPos(pausePos);
	pauseSprite_->Update();

	backSprite_ = std::make_unique<Sprite>();
	backSprite_->Ini();
	backSprite_->SetTexture(TextureManager::GetInstance()->GetTexture("White1280x720"));
	backSprite_->SetAnchor(Vector2(0, 0));
	backSprite_->SetColor(Color(0, 0, 0, 200));
	backSprite_->SetScale(Vector2(2, 2));
}

void MainGameSyste::CostInit()
{
	powerLevel_ = 1;
	powerUpCost_.push_back(10);
	powerUpCost_.push_back(20);
	powerUpCost_.push_back(30);
	powerUpCost_.push_back(40);

	minoCountLevel_ = 0;

	for (uint32_t i = 0; i < 100; i++) {
		int32_t cost = 50 + i * 20;
		minoCountUpCost_.push_back(cost);
	}
}

void MainGameSyste::Update()
{
	if (gameState_ != State::PAUSE &&
		gameState_ != State::GAMEOVER) {
		enemyManager_.Update();
		panel_->Update();

		if (enemyManager_.GetIsAllEnemyDestroy() == false) {
			gameState_ = State::GAME;
		}
		else {
			gameState_ = State::CLEAR;
		}
	}

	if (gameState_ == State::GAME) {
		//�G�̍U��
		if (nowTurn_ == Turn::PLAYER) {
			TurnPlayer();
			if (minos_.size() > 0) {
				panel_->SetUpdateType(UpdateType::All);
			}
			else {
				panel_->SetUpdateType(UpdateType::SpriteOnly);
			}
		}
		//�G�̍U��
		else if (nowTurn_ == Turn::ENEMY) {
			TurnEnemy();
			panel_->SetUpdateType(UpdateType::SpriteOnly);
		}
		//�^�[������シ��
		else if (nowTurn_ == Turn::CHANGE) {
			//�^�[�����`�F���W����
			TurnChange();
			panel_->SetUpdateType(UpdateType::SpriteOnly);
		}

		//�O�̃^�[�����ǂ����̃^�[�����L�^���Ă���
		if (nowTurn_ != Turn::CHANGE) {
			prevTurn_ = nowTurn_;
		}

		MinoCountUp();

		if (pauseButton_->GetIsCollision()) {
			if (MouseInput::GetInstance()->IsMouseTrigger(MOUSE_LEFT)) {
				gameState_ = State::PAUSE;
				SoundManager::Play("Click_1SE", false, 1.0f);
			}
		}

		attackButton_->Update();
		pauseButton_->Update();
	}
	//�N���A������
	else if (gameState_ == State::CLEAR) {
		panel_->SetUpdateType(UpdateType::SpriteOnly);

		if (MouseInput::GetInstance()->IsMouseTrigger(MOUSE_LEFT)) {
			if (titleButton_->GetIsCollision())
			{

				SceneManager::SetChangeStart(SceneName::Title);
			}
		}
	}
	else if (gameState_ == State::PAUSE) {
		if (MouseInput::GetInstance()->IsMouseTrigger(MOUSE_LEFT)) {
			if (titleButton_->GetIsCollision())
			{
				SceneManager::SetChangeStart(SceneName::Title);
				SoundManager::Play("Click_2SE", false, 1.0f);
			}
			if (backButton_->GetIsCollision())
			{
				gameState_ = State::GAME;
				SoundManager::Play("Click_2SE", false, 1.0f);
			}
		}

		titleButton_->SetPos(uiDownPos_);
		backButton_->SetPos(uiUpPos_);

		backButton_->Update();
		pauseSprite_->Update();
	}

	if (player_->GetIsAlive() == false) {
		gameState_ = State::GAMEOVER;
		panel_->SetUpdateType(UpdateType::SpriteOnly);
	}

	if (enemyManager_.GetIsChangeNowEnemy() || enemyManager_.GetNowEnemy() == nullptr) {
		enemy_ = enemyManager_.GetNowEnemy();
		enemyManager_.SetIsChangeNowEnemy(false);
	}

	nextMinoDrawer_.Update(minos_);
	
	int32_t cost = minoCountUpCost_.at(minoCountLevel_);
	int32_t nowEmptyPanelNum = panel_->GetTotalEmptyPanelNum();
	minoCounterDrawer_.Update(cost - nowEmptyPanelNum);

	// �J�����X�V
	cameraManager_->Update();

	if (gameState_ == State::CLEAR ||
		gameState_ == State::GAMEOVER ||
		gameState_ == State::PAUSE)
	{
		//�N���A�̎��̓^�C�g���ɖ߂�X�v���C�g�����L���ɂ���
		titleButton_->Update();
		//�Q�[���I�[�o�[
		if (gameState_ == State::GAMEOVER) {
			GameOverUpdate();
		}
	}

	mouseUi_.Update();
	backSprite_->Update();
}

void MainGameSyste::DrawSprite()
{
	panel_->DrawSprite();
	enemyManager_.Draw();

	attackButton_->Draw();
	nextMinoDrawer_.Draw();
	minoCounterDrawer_.Draw();
	mouseUi_.Draw();
	pauseButton_->Draw();
}

void MainGameSyste::DrawSpriteFront()
{

	if (gameState_ == State::CLEAR ||
		gameState_ == State::GAMEOVER ||
		gameState_ == State::PAUSE)
	{
		backSprite_->Draw();
		//�N���A�̎��̓^�C�g���ɖ߂�X�v���C�g�����L���ɂ���
		titleButton_->Draw();

		if (gameState_ == State::GAMEOVER) {
			retryButton_->Draw();
		}

		if (gameState_ == State::PAUSE) {
			backButton_->Draw();
			pauseSprite_->Draw();
		}
	}
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

	if (gameState_ == State::CLEAR)gameStatestring += "Clear";
	else if (gameState_ == State::GAME) gameStatestring += "fighting";
	else if (gameState_ == State::GAMEOVER) gameStatestring += "GAMEOVER";

	ImGui::Text(gameStatestring.c_str());

	ImGui::End();

	ImGui::Begin("Cost");

	ImGui::Text("minoCountUpCost : %d , Now : %d", minoCountUpCost_.at(powerLevel_ - 1), panel_->GetEmptyPanelNum());

	ImGui::End();

	/*minoCountUpButton_->DrawImgui();
	attackButton_->DrawImgui();*/
}

void MainGameSyste::ReloadMino()
{
	//minos_.clear();
	for (uint32_t i = 0; minos_.size() < reloadMinoNum_; i++) {
		//�~�m���X�g�ɖ����Ƃ��ɕ�[����
		if (minosList_.size() == 0) {
			for (uint32_t j = 0; j < 7; j++) {
				minosList_.push_back((MinoType)j);
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
		if (enemyManager_.GetNowEnemy() != nullptr) {
			enemyManager_.GetNowEnemy()->AttackAnimation();
		}
	}
	//�G�̃^�[���������玩���̃^�[����
	else if (prevTurn_ == Turn::ENEMY) {
		nowTurn_ = Turn::PLAYER;
		//�~�m�������[�h����
		ReloadMino();
		panel_->ReDoReset();

		if (panel_->GetPanelReset()) {
			panel_->PanelReset();
		}

		int32_t powerUp = panel_->GetStateUpValue().attackUp_;
		player_->AddAttack(powerUp);
		int32_t recovery = panel_->GetStateUpValue().recoverUp_;
		player_->Recovery(recovery);
		int32_t luck = panel_->GetStateUpValue().luckUp_;
		player_->AddLuck(luck);
		int32_t health = panel_->GetStateUpValue().healthUp_;
		player_->AddHealth(health);

		panel_->ResetStateUp();
	}
	prevTurn_ = nowTurn_;
}

void MainGameSyste::TurnPlayer()
{
	redoCoolTime_.AddTime(1);
	if (minos_.size() > 0) {
		panel_->ChangeMinoAnimation(minos_[0]);
	}

	//�p�l���̐ݒu������������
	if (panel_->GetisSetComplete()) {
		panel_->SetisSetComplete(false);
		panel_->SetRotNum(0);
		//�z�u�o�����~�m������
		if (minos_.size() > 0) {
			minos_.erase(minos_.begin());
		}

		if (minos_.size() <= 0 || panel_->GetIsAllFill()) {
			player_->AttackAnimation(panel_->GetDisplayPanel());
		}
	}
	//���h�D�@�\
	if (Key::TriggerKey(DIK_Z)) {
		if (redoCoolTime_.GetIsEnd()) {
			panel_->ReDo(&minos_);
		}
	}

	//�c��̐���0�ɂȂ����ꍇ�����ׂẴ}�X�𖄂߂����^�[�����I������
	if (minos_.size() <= 0 || panel_->GetIsAllFill() || isNext_ == true) {
		panel_->SetUpdateType(UpdateType::SpriteOnly);
		if (player_->GetRotTimEnd()) {
			//�p�l���X�V
			panel_->PanelUpdate();
			panel_->SetIsAllFill(false);
			//�G�Ƀ_���[�W��^����
			int32_t damage = panel_->GetAttackPanelNum() * player_->GetAttackPower();
			enemy_->Damage(damage);
			nowTurn_ = Turn::CHANGE;

			float pitch = RRandom::RandF(0.7f, 1.f);
			SoundManager::Play("Attack", false, 1.0f, pitch);

			isNext_ = false;
		}
	}
	//�U���{�^������������
	if (attackButton_->GetIsCollision()) {
		if (MouseInput::GetInstance()->IsMouseTrigger(MOUSE_LEFT)) {
			if (isNext_ == false) {
				SoundManager::Play("Click_2SE", false, 1.0f);
				isNext_ = true;
				player_->AttackAnimation(panel_->GetDisplayPanel());
			}
		}
	}
}

void MainGameSyste::TurnEnemy()
{
	//�v���C���[���_���[�W���󂯂�
	if (enemyManager_.GetIsChangeNowEnemy() == false) {
		if (enemyManager_.GetNowEnemy()->GetIsEndAttack()) {
			player_->Damage(enemy_->GetAttackPower());

			float pitch = RRandom::RandF(0.7f, 1.f);
			SoundManager::Play("Attack", false, 1.0f, pitch);

			//�������I�������V�[�����`�F���W����
			nowTurn_ = Turn::CHANGE;
		}
	}
	else {
		//�������I�������V�[�����`�F���W����
		nowTurn_ = Turn::CHANGE;
	}

}

void MainGameSyste::GameOverUpdate()
{
	retryButton_->Update();

	titleButton_->SetPos(uiDownPos_);
	retryButton_->SetPos(uiUpPos_);

	if (MouseInput::GetInstance()->IsMouseTrigger(MOUSE_LEFT)) {
		if (titleButton_->GetIsCollision())
		{
			SceneManager::SetChangeStart(SceneName::Title);
		}
		else if (retryButton_->GetIsCollision())
		{

			SceneManager::SetChangeStart(SceneName::Game);
		}
	}
}

void MainGameSyste::MinoCountUp()
{
	const int32_t cost = minoCountUpCost_.at(minoCountLevel_);
	int32_t nowEmptyPanelNum = panel_->GetTotalEmptyPanelNum();
	//�󔒂̃p�l�����R�X�g�����������
	if (cost <= nowEmptyPanelNum) {
		minoCountLevel_++;
		reloadMinoNum_++;

		size_t costMaxNum = minoCountUpCost_.size() - 1;
		minoCountLevel_ = (uint32_t)Min(costMaxNum, (size_t)minoCountLevel_);
		//panel_->PanelReset();
	}
}

#pragma region �`���[�g���A��
void MainGameSyste::TutorialInit()
{
	panel_ = std::make_unique<Panel>();

	nowTurn_ = Turn::PLAYER;
	gameState_ = State::GAME;
	//�^�[�����Ƃɕ�[����~�m�̐�
	reloadMinoNum_ = 5;

	ReloadMino();

	nextMinoDrawer_.Initialize();
	enemy_ = enemyManager_.GetNowEnemy();

	// �J�����擾 + ������
	cameraManager_ = YCameraManager::GetInstance();
	cameraManager_->Initialize();

	SpriteInit();
	CostInit();

	redoCoolTime_.SetLimitTime(5);

	textFrameSprite_ = std::make_unique<Sprite>();
	textFrameSprite_->Ini();
	textFrameSprite_->SetTexture(TextureManager::GetInstance()->GetTexture("TextFrame"));
	textFrameSprite_->SetPos(Vector2(300, 660));

	textSprite_ = std::make_unique<Sprite>();
	textSprite_->Ini();
	textSprite_->SetTexture(TextureManager::GetInstance()->GetTexture("TutorialText"));
	textSprite_->SetPos(Vector2(300, 660));
	textSprite_->SetTex_Size(Vector2(320, 120));
	Vector2 textureSize = TextureManager::GetInstance()->GetTexture("TutorialText")->size_;
	textureSize = {
		1.f / 6.f,
		1.f / 4.f,
	};
	textSprite_->SetScale(textureSize);
}

void MainGameSyste::TutorialUpdate()
{
	if (gameState_ != State::PAUSE &&
		gameState_ != State::GAMEOVER) {
		enemyManager_.Update();
		panel_->Update();

		if (enemyManager_.GetIsAllEnemyDestroy() == false) {
			gameState_ = State::GAME;
		}
		else {
			gameState_ = State::CLEAR;
		}
	}

	if (tutorialstep_ == TutorialStep::Set) {
		
		if (tutorialIndexX_ == 0) {
			if (MouseInput::GetInstance()->IsMouseTrigger(MOUSE_LEFT)) {
				tutorialIndexX_++;
			}
		}
		if (tutorialIndexX_ == 1) {
			if (panel_->GetisSetComplete()) {
				if (tutorialIndexX_ == 1)tutorialIndexX_++;
			}
		}
		//�I�����W�̃p�l���́c
		else if (tutorialIndexX_ == 2) {
			panel_->SetUpdateType(UpdateType::SpriteOnly);
			if (MouseInput::GetInstance()->IsMouseTrigger(MOUSE_LEFT)) {
				tutorialIndexX_++;
			}
		}
		//���p�l���͎��̃^�[���Łc
		else if (tutorialIndexX_ == 3) {
			panel_->SetUpdateType(UpdateType::SpriteOnly);
			if (MouseInput::GetInstance()->IsMouseTrigger(MOUSE_LEFT)) {
				tutorialIndexX_++;
			}
		}
		// �S�Ẵp�l���𖄂߂邩�U���{�^�����c
		else if (tutorialIndexX_ == 4) {
			panel_->SetUpdateType(UpdateType::All);
			if (attackButton_->GetIsCollision()) {
				if (MouseInput::GetInstance()->IsMouseTrigger(MOUSE_LEFT)) {
					tutorialIndexX_++;
					tutorialstep_ = TutorialStep::StatusUp;
				}
			}
			if (panel_->GetIsAllFill()) {
				tutorialIndexX_++;
				tutorialstep_ = TutorialStep::StatusUp;
			}
		}
		
	}
	else if (tutorialstep_ == TutorialStep::StatusUp) {
		//��{�͂�������ăp�l�����c
		if (tutorialIndexX_ == 5) {
			if (MouseInput::GetInstance()->IsMouseTrigger(MOUSE_LEFT)) {
				tutorialIndexX_ = 0;
				tutorialIndexY_++;
			}
		}
		//�����΂񂻂Ƃ���ɒu���ƃp�l�������Z�b�g�c
		else if (tutorialIndexX_ == 0) {
			if (MouseInput::GetInstance()->IsMouseTrigger(MOUSE_LEFT)) {
				tutorialIndexX_++;
			}
		}
		//�X�e�[�^�X���オ���
		else if (tutorialIndexX_ == 1) {
			if (MouseInput::GetInstance()->IsMouseTrigger(MOUSE_LEFT)) {
				tutorialIndexX_++;
			}
		}
		//�O���܂ł̂ς��Ă݂悤
		else if (tutorialIndexX_ == 2) {
			if (panel_->GetPanelReset()) {
				tutorialstep_ = TutorialStep::PanelNumUp;
				tutorialIndexY_++;
				tutorialIndexX_ = 0;
			}
		}

	}
	else if (tutorialstep_ == TutorialStep::PanelNumUp) {
		if (tutorialIndexX_ == 3) {
			if (MouseInput::GetInstance()->IsMouseTrigger(MOUSE_LEFT)) {
				tutorialIndexX_ = 0;
				tutorialIndexY_++;
			}
		}
		//�p�l�����������������������΁c
		else if (tutorialIndexX_ == 0) {
			if (MouseInput::GetInstance()->IsMouseTrigger(MOUSE_LEFT)) {
				tutorialIndexX_++;
			}
		}
		//�P�^�[���ɒu����p�[�c�̐����c
		else if (tutorialIndexX_ == 1) {
			if (MouseInput::GetInstance()->IsMouseTrigger(MOUSE_LEFT)) {
				tutorialIndexY_++;
				tutorialIndexX_ = 0;
				tutorialstep_ = TutorialStep::End;
			}
		}
	}
	else if (tutorialstep_ == TutorialStep::End) {
		if (tutorialIndexX_ == 0) {
			if (MouseInput::GetInstance()->IsMouseTrigger(MOUSE_LEFT)) {
				tutorialIndexX_++;
			}
		}
		else if (tutorialIndexX_ == 1) {
			if (MouseInput::GetInstance()->IsMouseTrigger(MOUSE_LEFT)) {
				SceneManager::SetChangeStart(SceneName::Title);
			}
		}
	}

	if (gameState_ == State::GAME) {

		panel_->SetUpdateType(UpdateType::All);
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

		MinoCountUp();

		if (pauseButton_->GetIsCollision()) {
			if (MouseInput::GetInstance()->IsMouseTrigger(MOUSE_LEFT)) {
				gameState_ = State::PAUSE;
				SoundManager::Play("Click_1SE", false, 1.0f);
			}
		}

		attackButton_->Update();
		pauseButton_->Update();
	}
	//�N���A������
	else if (gameState_ == State::CLEAR) {
		panel_->SetUpdateType(UpdateType::SpriteOnly);

		if (MouseInput::GetInstance()->IsMouseTrigger(MOUSE_LEFT)) {
			if (titleButton_->GetIsCollision())
			{

				SceneManager::SetChangeStart(SceneName::Title);
			}
		}
	}
	else if (gameState_ == State::PAUSE) {
		if (MouseInput::GetInstance()->IsMouseTrigger(MOUSE_LEFT)) {
			if (titleButton_->GetIsCollision())
			{
				SceneManager::SetChangeStart(SceneName::Title);
				SoundManager::Play("Click_2SE", false, 1.0f);
			}
			if (backButton_->GetIsCollision())
			{
				gameState_ = State::GAME;
				SoundManager::Play("Click_2SE", false, 1.0f);
			}
		}

		titleButton_->SetPos(uiDownPos_);
		backButton_->SetPos(uiUpPos_);

		backButton_->Update();
		pauseSprite_->Update();
	}

	if (player_->GetIsAlive() == false) {
		gameState_ = State::GAMEOVER;
		panel_->SetUpdateType(UpdateType::SpriteOnly);
	}

	if (enemyManager_.GetIsChangeNowEnemy() || enemyManager_.GetNowEnemy() == nullptr) {
		enemy_ = enemyManager_.GetNowEnemy();
		enemyManager_.SetIsChangeNowEnemy(false);
	}

	nextMinoDrawer_.Update(minos_);
	int32_t cost = minoCountUpCost_.at(minoCountLevel_);
	int32_t nowEmptyPanelNum = panel_->GetTotalEmptyPanelNum();
	minoCounterDrawer_.Update(cost - nowEmptyPanelNum);

	// �J�����X�V
	cameraManager_->Update();

	if (gameState_ == State::CLEAR ||
		gameState_ == State::GAMEOVER ||
		gameState_ == State::PAUSE)
	{
		//�N���A�̎��̓^�C�g���ɖ߂�X�v���C�g�����L���ɂ���
		titleButton_->Update();
		//�Q�[���I�[�o�[
		if (gameState_ == State::GAMEOVER) {
			GameOverUpdate();
		}
	}

	mouseUi_.Update();
	backSprite_->Update();
	textFrameSprite_->Update();
	textSprite_->Update();
	textSprite_->SetTex_LeftTop(
		Vector2(tutorialIndexX_ * 320.f,
			tutorialIndexY_ * 128.f));


	if (tutorialIndexY_ == 0) {
		if (tutorialIndexX_ == 0) {
			panel_->SetUpdateType(UpdateType::SpriteOnly);
		}
		else if (tutorialIndexX_ == 1) {
			panel_->SetUpdateType(UpdateType::All);
		}
		else if (tutorialIndexX_ == 2) {
			panel_->SetUpdateType(UpdateType::SpriteOnly);
		}
		else if (tutorialIndexX_ == 3) {
			panel_->SetUpdateType(UpdateType::SpriteOnly);
		}

	}
	else if (tutorialIndexY_ == 1) {
		if (tutorialIndexX_ == 0) {
			panel_->SetUpdateType(UpdateType::SpriteOnly);
		}
		else if (tutorialIndexX_ == 1) {
			panel_->SetUpdateType(UpdateType::SpriteOnly);
		}
		else if (tutorialIndexX_ == 2) {
			panel_->SetUpdateType(UpdateType::All);
		}
		else if (tutorialIndexX_ == 3) {
			panel_->SetUpdateType(UpdateType::SpriteOnly);
		}
		else if (tutorialIndexX_ == 4) {
			panel_->SetUpdateType(UpdateType::All);
		}
		else if (tutorialIndexX_ == 5) {
			panel_->SetUpdateType(UpdateType::SpriteOnly);
		}
	}
	else if (tutorialIndexY_ == 2) {
		if (tutorialIndexX_ == 0) {
			panel_->SetUpdateType(UpdateType::SpriteOnly);
		}
		else if (tutorialIndexX_ == 1) {
			panel_->SetUpdateType(UpdateType::SpriteOnly);
		}
		else if (tutorialIndexX_ == 2) {
			panel_->SetUpdateType(UpdateType::SpriteOnly);
		}
		else if (tutorialIndexX_ == 3) {
			panel_->SetUpdateType(UpdateType::SpriteOnly);
		}
	}
	else if (tutorialIndexY_ == 3) {
		if (tutorialIndexX_ == 3) {
			panel_->SetUpdateType(UpdateType::SpriteOnly);
		}
		else {

			panel_->SetUpdateType(UpdateType::SpriteOnly);
		}
	}

}

void MainGameSyste::TutorialDraw()
{
	panel_->DrawSprite();
	enemyManager_.Draw();

	attackButton_->Draw();
	nextMinoDrawer_.Draw();
	mouseUi_.Draw();
	pauseButton_->Draw();

	textFrameSprite_->Draw();
	textSprite_->Draw();
}
void MainGameSyste::TutorialDrawFront()
{
	if (gameState_ == State::CLEAR ||
		gameState_ == State::GAMEOVER ||
		gameState_ == State::PAUSE)
	{
		backSprite_->Draw();
		//�N���A�̎��̓^�C�g���ɖ߂�X�v���C�g�����L���ɂ���
		titleButton_->Draw();

		if (gameState_ == State::GAMEOVER) {
			retryButton_->Draw();
		}

		if (gameState_ == State::PAUSE) {
			backButton_->Draw();
			pauseSprite_->Draw();
		}
	}
}
void MainGameSyste::TutorialDrawImGui()
{
	ImGui::Begin("Tutorial");
	std::string string = "TutorialStep : ";

	if (tutorialstep_ == TutorialStep::Set)string += "Set";
	if (tutorialstep_ == TutorialStep::StatusUp)string += "StatusUp";
	if (tutorialstep_ == TutorialStep::PanelNumUp)string += "PanelNumUp";

	ImGui::Text(string.c_str());

	ImGui::End();

	ImGui::Begin("Mouse");

	float pos[2] = {
		MouseInput::GetInstance()->mPos_.x,
		MouseInput::GetInstance()->mPos_.y
	};

	ImGui::DragFloat2("pos", pos);

	ImGui::End();
}
#pragma endregion