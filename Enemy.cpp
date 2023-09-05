#include "Enemy.h"
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
	sprite_->Update();
}

void Enemy::Draw()
{
	sprite_->Draw();
}

void Enemy::DrawImGui()
{
	ImGui::Begin("Enemy");

	ImGui::Text("HP : %d", health_);

	ImGui::End();
}
