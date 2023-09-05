#include "Player.h"
#include <imgui.h>

void Player::Initialize()
{
	sprite_ = std::make_unique<Sprite>();
	sprite_->Ini();
	sprite_->SetTexture(TextureManager::GetInstance()->GetTexture("Player"));
	sprite_->SetPos(Vector2(200, 500));
	
	health_ = 100;
	attackpower_ = 2;
}

void Player::Update()
{
	sprite_->Update();
}

void Player::Draw()
{
	sprite_->Draw();
}

void Player::DrawImGui()
{
	ImGui::Begin("player");
	ImGui::Text("HP : %d", health_);
	ImGui::End();
}
