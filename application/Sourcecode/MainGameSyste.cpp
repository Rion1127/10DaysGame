#include "MainGameSyste.h"
#include "RRandom.h"
#include "SceneManager.h"

using YGame::YCameraManager;

MainGameSyste::MainGameSyste()
{
	panel_ = std::make_unique<Panel>();

	nowTurn_ = Turn::PLAYER;
	gameState_ = State::GAME;
	//ターンごとに補充するミノの数
	reloadMinoNum_ = 5;

	ReloadMino();

	nextMinoDrawer_.Initialize();
	enemy_ = enemyManager_.GetNowEnemy();

	// カメラ取得 + 初期化
	cameraManager_ = YCameraManager::GetInstance();
	cameraManager_->Initialize();

	SpriteInit();
	CostInit();

	redoCoolTime_.SetLimitTime(5);
}

void MainGameSyste::SpriteInit()
{
	uiUpPos_ = {
		WinAPI::GetWindowSize().x / 2.f,
		WinAPI::GetWindowSize().y / 1.3f
	};
	titleButton_ = std::make_unique<Button>(uiUpPos_);
	titleButton_->SetTexture(TextureManager::GetInstance()->GetTexture("TitleButton"));
	uiDownPos_ = {
		WinAPI::GetWindowSize().x / 2.f,
		WinAPI::GetWindowSize().y / 1.1f
	};
	retryButton_ = std::make_unique<Button>(uiUpPos_);
	retryButton_->SetTexture(TextureManager::GetInstance()->GetTexture("Retry"));

	minoCountUpPos_ = {
		80.f,
		400.f
	};
	minoCountUpButton_ = std::make_unique<Button>(minoCountUpPos_);
	minoCountUpButton_->SetTexture(TextureManager::GetInstance()->GetTexture("MinoCouintUp"));

	attackPos_ = {
		80.f,
		300.f
	};
	attackButton_ = std::make_unique<Button>(attackPos_);
	attackButton_->SetTexture(TextureManager::GetInstance()->GetTexture("AttackButton"));
}

void MainGameSyste::CostInit()
{
	powerLevel_ = 1;
	powerUpCost_.push_back(10);
	powerUpCost_.push_back(20);
	powerUpCost_.push_back(30);
	powerUpCost_.push_back(40);

	minoCountLevel_ = 1;
	minoCountUpCost_.push_back(50);
	minoCountUpCost_.push_back(60);
	minoCountUpCost_.push_back(70);
	minoCountUpCost_.push_back(80);
	minoCountUpCost_.push_back(90);
}

void MainGameSyste::Update()
{
	enemyManager_.Update();
	panel_->Update();
	if (enemyManager_.GetIsAllEnemyDestroy() == false) {
		gameState_ = State::GAME;
		panel_->SetUpdateType(UpdateType::All);
		//敵の攻撃
		if (nowTurn_ == Turn::PLAYER) {
			TurnPlayer();
		}
		//敵の攻撃
		else if (nowTurn_ == Turn::ENEMY) {
			TurnEnemy();
		}
		//ターンを交代する
		else if (nowTurn_ == Turn::CHANGE) {
			//ターンをチェンジする
			TurnChange();
		}

		//前のターンがどっちのターンか記録しておく
		if (nowTurn_ != Turn::CHANGE) {
			prevTurn_ = nowTurn_;
		}

		if (MouseInput::GetInstance()->IsMouseTrigger(MOUSE_LEFT)) {
			//1ターンに置くパーツの数を増やす
			if (minoCountUpButton_->GetIsCollision()) {
				MinoCountUp();
			}
		}
		minoCountUpButton_->Update();
		attackButton_->Update();
	}
	//クリアしたら
	else {
		gameState_ = State::CLEAR;
		panel_->SetUpdateType(UpdateType::SpriteOnly);

		if (MouseInput::GetInstance()->IsMouseTrigger(MOUSE_LEFT)) {
			if (titleButton_->GetIsCollision())
			{

				SceneManager::SetChangeStart(SceneName::Title);
			}
		}
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

	// カメラ更新
	cameraManager_->Update();

	if (gameState_ == State::CLEAR ||
		gameState_ == State::GAMEOVER)
	{
		//クリアの時はタイトルに戻るスプライトだけ有効にする
		titleButton_->Update();
		//ゲームオーバー
		if (gameState_ == State::GAMEOVER) {
			GameOverUpdate();
		}
	}

	mouseUi_.Update();
}

void MainGameSyste::DrawSprite()
{
	panel_->DrawSprite();
	enemyManager_.Draw();
	if (gameState_ == State::CLEAR ||
		gameState_ == State::GAMEOVER)
	{
		//クリアの時はタイトルに戻るスプライトだけ有効にする
		titleButton_->Draw();

		if (gameState_ == State::GAMEOVER) {
			retryButton_->Draw();
		}
	}
	
	minoCountUpButton_->Draw();
	attackButton_->Draw();
	nextMinoDrawer_.Draw();
	mouseUi_.Draw();
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

	ImGui::Text("powerUpCost : %d , Now : %d", powerUpCost_.at(powerLevel_ - 1), panel_->GetEmptyPanelNum());
	ImGui::Text("minoCountUpCost : %d , Now : %d", minoCountUpCost_.at(powerLevel_ - 1), panel_->GetEmptyPanelNum());

	ImGui::End();

	/*minoCountUpButton_->DrawImgui();
	attackButton_->DrawImgui();*/
}

void MainGameSyste::ReloadMino()
{
	minos_.clear();
	for (uint32_t i = 0; i < reloadMinoNum_; i++) {
		//ミノリストに無いときに補充する
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
	//自分のターンだったら敵のターンへ
	if (prevTurn_ == Turn::PLAYER) {
		nowTurn_ = Turn::ENEMY;
	}
	//敵のターンだったら自分のターンへ
	else if (prevTurn_ == Turn::ENEMY) {
		nowTurn_ = Turn::PLAYER;
		//ミノをリロードする
		ReloadMino();
		panel_->ReDoReset();

		int32_t powerUp = panel_->GetPowerUpPanelNum() * 2;
		player_->AddAttackPower(powerUp);
		int32_t recovery = panel_->GetRecoveryPanelNum() * 10;
		player_->Recovery(recovery);
	}
	prevTurn_ = nowTurn_;
}

void MainGameSyste::TurnPlayer()
{
	redoCoolTime_.AddTime(1);
	if (minos_.size() > 0) {
		panel_->ChangeMinoAnimation(minos_[0]);
	}

	//パネルの設置が成功したら
	if (panel_->GetisSetComplete()) {
		panel_->SetisSetComplete(false);
		panel_->SetRotNum(0);
		//配置出来たミノを消す
		minos_.erase(minos_.begin());

		if (minos_.size() <= 0 || panel_->GetIsAllFill()) {
			player_->AttackAnimation(panel_->GetDisplayPanel());
		}
	}
	//リドゥ機能
	if (Key::TriggerKey(DIK_Z)) {
		if (redoCoolTime_.GetIsEnd()) {
			panel_->ReDo(&minos_);
		}
	}

	//残りの数が0になった場合かすべてのマスを埋めた時ターンを終了する
	if (minos_.size() <= 0 || panel_->GetIsAllFill()) {
		panel_->SetUpdateType(UpdateType::SpriteOnly);
		if (player_->GetRotTimEnd()) {
			//パネル更新
			panel_->PanelUpdate();
			panel_->SetIsAllFill(false);
			//敵にダメージを与える
			int32_t damage = panel_->GetAttackPanelNum() * player_->GetAttackPower();
			enemy_->Damage(damage);
			nowTurn_ = Turn::CHANGE;
		}
	}
	//攻撃ボタンを押したら
	if (attackButton_->GetIsCollision()) {
		if (MouseInput::GetInstance()->IsMouseTrigger(MOUSE_LEFT)) {
			if (minos_.size() > 0) {
				minos_.clear();
				player_->AttackAnimation(panel_->GetDisplayPanel());
			}
		}
	}
}

void MainGameSyste::TurnEnemy()
{
	//プレイヤーがダメージを受ける
	if (enemyManager_.GetIsChangeNowEnemy() == false) {
		player_->Damage(enemy_->GetAttackPower());
		player_->AddPowerReset();
	}

	//処理が終わったらシーンをチェンジする
	nowTurn_ = Turn::CHANGE;
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
	const int32_t cost = minoCountUpCost_.at(minoCountLevel_ - 1);
	int32_t nowEmptyPanelNum = panel_->GetEmptyPanelNum();
	//空白のパネルがコストよりも多ければ
	if (cost <= nowEmptyPanelNum) {
		minoCountLevel_++;
		reloadMinoNum_++;
		panel_->PanelReset();
	}
}

#pragma region チュートリアル
void MainGameSyste::TutorialInit()
{
	panel_ = std::make_unique<Panel>();

	nowTurn_ = Turn::PLAYER;
	gameState_ = State::GAME;
	//ターンごとに補充するミノの数
	reloadMinoNum_ = 5;

	ReloadMino();

	nextMinoDrawer_.Initialize();
	enemy_ = enemyManager_.GetNowEnemy();

	// カメラ取得 + 初期化
	cameraManager_ = YCameraManager::GetInstance();
	cameraManager_->Initialize();

	SpriteInit();
	CostInit();

	redoCoolTime_.SetLimitTime(5);
}

void MainGameSyste::TutorialUpdate()
{
}

void MainGameSyste::TutorialDraw()
{
}
#pragma endregion