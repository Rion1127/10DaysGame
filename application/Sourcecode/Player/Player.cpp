#include "Player.h"
#include "YCameraManager.h"
#include <imgui.h>
#include "WinAPI.h"

void Player::Initialize()
{	
	sprite_ = std::make_unique<Sprite>();
	sprite_->Ini();
	sprite_->SetTexture(TextureManager::GetInstance()->GetTexture("Player"));

	Vector2 pos = {
		WinAPI::GetWindowSize().x / 3.4f,
		WinAPI::GetWindowSize().y / 5.f
	};
	sprite_->SetPos(pos);

	health_ = 100;
	attackpower_ = 2;

	// トランスフォーム
	trfm_.Initialize();
	trfm_.pos_ = Vector3(sprite_->GetPos().x, sprite_->GetPos().y, 0.0f);
	
	// アニメーション用
	sword_.Initialize(20, 20, &trfm_.m_);
}

void Player::Update()
{
	trfm_.UpdateMatrix({ YCameraManager::GetInstance()->GetCameraPos(), {}, {} });
	
	sprite_->Update(trfm_.m_);
	
	sword_.Update();
}

void Player::AttackAnimation(const std::vector<std::vector<int32_t>>& panelIndices)
{
	sword_.AttackAnimation(panelIndices);
}

void Player::Draw()
{
	sprite_->Draw();

	sword_.Draw();
}

void Player::DrawImGui()
{
	ImGui::Begin("player");
	ImGui::Text("HP : %d", health_);
	ImGui::End();
}
