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
	reloadMinoNum_ = 1;

	ReloadMino();

	nextMinoDrawer_.Initialize();
	enemy_ = enemyManager_.GetNowEnemy();

	// カメラ取得 + 初期化
	cameraManager_ = YCameraManager::GetInstance();
	cameraManager_->Initialize();

	SpriteInit();
	CostInit();
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
		WinAPI::GetWindowSize().x / 1.3f,
		WinAPI::GetWindowSize().y / 1.3f
	};
	minoCountUpButton_ = std::make_unique<Button>(minoCountUpPos_);
	minoCountUpButton_->SetTexture(TextureManager::GetInstance()->GetTexture("MinoCouintUp"));
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
			//1ターンに置くパーツの数を
			if (minoCountUpButton_->GetIsCollision()) {
				MinoCountUp();
			}
		}
		minoCountUpButton_->Update();
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
	nextMinoDrawer_.Draw();
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
	}
	prevTurn_ = nowTurn_;
}

void MainGameSyste::TurnPlayer()
{
	if (minos_.size() > 0) {
		panel_->ChangeMinoAnimation(minos_[0]);
	}

	//パネルの設置が成功したら
	if (panel_->GetisSetComplete()) {
		panel_->SetisSetComplete(false);
		//配置出来たミノを消す
		minos_.erase(minos_.begin());

		//残りの数が0になった場合かすべてのマスを埋めた時ターンを終了する
		if (minos_.size() <= 0 || panel_->GetIsAllFill()) {
			//パネル更新
			panel_->PanelUpdate();
			//敵にダメージを与える
			int32_t damage = panel_->GetAttackPanelNum() * player_->GetAttackPower();
			enemy_->Damage(damage);
			nowTurn_ = Turn::CHANGE;

			player_->AttackAnimation(panel_->GetDisplayPanel());
		}
	}
}

void MainGameSyste::TurnEnemy()
{
	//プレイヤーがダメージを受ける
	if (enemyManager_.GetIsChangeNowEnemy() == false) {
		player_->Damage(enemy_->GetAttackPower());
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
