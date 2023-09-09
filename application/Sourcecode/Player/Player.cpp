#include "Player.h"
#include "YCameraManager.h"
#include <imgui.h>
#include "WinAPI.h"

void Player::Initialize()
{	
	Vector3 pos = {
		WinAPI::GetWindowSize().x / 2.0f - 128.0f,
		WinAPI::GetWindowSize().y / 6.0f,
		0.0f
	};

	Vector3 scale = { 0.75f,0.75f,0.0f };

	health_ = 100;
	baseAttackpower_ = 2;
	isAlive_ = true;

	// トランスフォーム
	trfm_.Initialize();
	trfm_.pos_ = pos;
	trfm_.scale_ = scale;

	// アニメーション用
	drawer_.Initialize(YGame::YTransform::Status::Default(), &trfm_.m_);
	sword_.Initialize(20, 20, &trfm_.m_);
	hpBar_.Initialize({ {0.0f,96.0f,0.0f},{},{1.0f,1.0f,1.0f} }, &trfm_.m_, health_);
	damage_.Initialize({ {0.0f,-32.0f,0.0f},{},{0.5f,0.5f,1.0f} }, &trfm_.m_, 0);

	drawer_.MoveAnimation();
}

void Player::Update()
{	
	trfm_.UpdateMatrix({ YGame::YCameraManager::GetInstance()->GetCameraPos(), {}, {} });

	if (health_ <= 0) {
		isAlive_ = false;
	}
	attackpower_ = baseAttackpower_ + powerUpValue_;

	drawer_.Update();
	sword_.Update();
	hpBar_.Update();
	damage_.Update();
}

void Player::AttackAnimation(const std::vector<std::vector<int32_t>>& panelIndices)
{
	sword_.AttackAnimation(panelIndices);
}

void Player::Draw()
{
	drawer_.Draw();
	sword_.Draw();
	hpBar_.Draw();
	damage_.Draw();
}

void Player::DrawImGui()
{
	ImGui::Begin("player");
	ImGui::Text("HP : %d", health_);
	ImGui::Text("power : %d", attackpower_);
	ImGui::End();
}

void Player::Damage(int32_t damage)
{
	health_ -= damage;

	drawer_.HitAnimation();
	hpBar_.ChangeHPAnimation(health_);
	damage_.SetNumber(damage);
	damage_.DamageAnimation();
}

void Player::Recovery(int32_t health)
{
	health_ += health;
	hpBar_.ChangeHPAnimation(health_);
}

void Player::IdleAnimation()
{
	drawer_.IdleAnimation();
}

void Player::MoveAnimation()
{
	drawer_.MoveAnimation();
}
