#include "MainGameSyste.h"
#include "RRandom.h"

MainGameSyste::MainGameSyste()
{
	panel_ = std::make_unique<Panel>();

	nowTurn_ = Turn::PLAYER;
	//ターンごとに補充するミノの数
	reloadMinoNum_ = 2;

	ReloadMino();
}

void MainGameSyste::Update()
{
	panel_->Update();

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
		panel_->SetMinoType(minos_[0]);
	}

	//パネルの設置が成功したら
	if (panel_->GetisSetComplete()) {
		panel_->SetisSetComplete(false);
		//配置出来たミノを消す
		minos_.erase(minos_.begin());

		//残りの数が0になった場合ターンを終了する
		if (minos_.size() <= 0) {
			//パネル更新
			panel_->PanelUpdate();
			reloadMinoNum_ = 2;
			//敵にダメージを与える
			int32_t damage = panel_->GetAttackPanelNum() * player_->GetAttackPower();
			enemy_->Damage(damage);
			nowTurn_ = Turn::CHANGE;
		}
	}
}

void MainGameSyste::TurnEnemy()
{
	//プレイヤーがダメージを受ける
	if (enemy_->GetIsAlive()) {
		player_->Damage(enemy_->GetAttackPower());
	}

	//処理が終わったらシーンをチェンジする
	nowTurn_ = Turn::CHANGE;
}
