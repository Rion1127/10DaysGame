#include "MainGameSyste.h"

MainGameSyste::MainGameSyste()
{
	panel_ = std::make_unique<Panel>();

	nowTurn_ = Turn::PLAYER;
	//ターンごとに補充するミノの数
	reloadMinoNum_ = 2;
}

void MainGameSyste::Update()
{
	panel_->Update();
	//パネルの設置が成功したら
	if (panel_->GetisSetComplete()) {
		panel_->SetisSetComplete(false);

		reloadMinoNum_--;
		//残りの数が0になった場合ターンを終了する
		if (reloadMinoNum_ <= 0) {
			//プレイヤーターン終了演出はここへ


			nowTurn_ = Turn::CHANGE;
		}
	}

	//敵の攻撃
	if (nowTurn_ == Turn::ENEMY) {
		player_->Damage(10);
		//エネミーターン終了演出はここへ

		//処理が終わったらシーンをチェンジする
		nowTurn_ = Turn::CHANGE;
	}

	//ターンを交代する
	if (nowTurn_ == Turn::CHANGE) {
		//シーンチェンジ演出はここへ


		//自分のターンだったら敵のターンへ
		if (prevTurn_ == Turn::PLAYER) {
			nowTurn_ = Turn::ENEMY;

			//パネル更新
			panel_->PanelUpdate();
			reloadMinoNum_ = 2;
			int32_t damage = panel_->GetAttackPanelNum() * player_->GetAttackPower();
			enemy_->Damage(damage);
		}
		//敵のターンだったら自分のターンへ
		else if (prevTurn_ == Turn::ENEMY) {
			nowTurn_ = Turn::PLAYER;
			
		}
		prevTurn_ = nowTurn_;
	}
	//前のターンがどっちのターンか記録しておく
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
