#include "Enemy.h"
#include "YCameraManager.h"
#include <imgui.h>

Enemy::Enemy(int32_t health, int32_t attackPower, int32_t guard) :
	IEnemy(health, attackPower, guard)
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

	statusTrfm_.UpdateMatrix();
	statusFrame_.Update(statusTrfm_.m_);
	for (size_t i = 0; i < status_.size(); i++)
	{
		status_[i].Update();
	}
}

void Enemy::Draw()
{
	drawer_.Draw();
	hpBar_.Draw();
	damage_.Draw();
	statusFrame_.Draw();
	for (size_t i = 0; i < status_.size(); i++)
	{
		status_[i].Draw();
	}
}

void Enemy::DrawImGui()
{
	ImGui::Begin("Enemy");

	ImGui::Text("HP : %d", health_);

	ImGui::End();
}
