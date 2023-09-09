#include "Enemy.h"
#include "YCameraManager.h"
#include <imgui.h>

Enemy::Enemy(int32_t health, int32_t attackPower) :
	IEnemy(health, attackPower)
{
}

void Enemy::Initialize() 
{
}

void Enemy::Update()
{
	trfm_.UpdateMatrix({ YGame::YCameraManager::GetInstance()->GetCameraPos(), {}, {} });

	drawer_.Update();
	hpBar_.Update();
	damage_.Update();
}

void Enemy::Draw()
{
	drawer_.Draw();
	hpBar_.Draw();
	damage_.Draw();
}

void Enemy::DrawImGui()
{
	ImGui::Begin("Enemy");

	ImGui::Text("HP : %d", health_);

	ImGui::End();
}
