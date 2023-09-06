#include "Player.h"
#include "YCameraManager.h"
#include <imgui.h>
#include "WinAPI.h"

void Player::Initialize()
{	
	Vector3 pos = {
		WinAPI::GetWindowSize().x / 3.4f,
		WinAPI::GetWindowSize().y / 5.f,
		0.0f
	};

	health_ = 100;
	attackpower_ = 2;

	// �g�����X�t�H�[��
	trfm_.Initialize();
	trfm_.pos_ = pos;

	// �A�j���[�V�����p
	drawer_.Initialize(YGame::YTransform::Status::Default(), &trfm_.m_);
	sword_.Initialize(20, 20, &trfm_.m_);
}

void Player::Update()
{
	trfm_.UpdateMatrix({ YGame::YCameraManager::GetInstance()->GetCameraPos(), {}, {} });

	drawer_.Update();
	sword_.Update();
}

void Player::AttackAnimation(const std::vector<std::vector<int32_t>>& panelIndices)
{
	sword_.AttackAnimation(panelIndices);
}

void Player::Draw()
{
	drawer_.Draw();
	sword_.Draw();
}

void Player::DrawImGui()
{
	ImGui::Begin("player");
	ImGui::Text("HP : %d", health_);
	ImGui::End();
}

void Player::Damage(int32_t damage)
{
	health_ -= damage;

	drawer_.HitAnimation();
}
