#include "Enemy.h"
#include "YCameraManager.h"
#include <imgui.h>

Enemy::Enemy(int32_t health, int32_t attackPower) :
	IEnemy(health, attackPower)
{
}

void Enemy::Initialize() 
{
	trfm_.Initialize();
	trfm_.pos_ = Vector3(sprite_->GetPos().x, sprite_->GetPos().y, 0.0f);

	hitActor_.Initialize();
}

void Enemy::Update()
{
	hitActor_.Update();
	
	Vector3 pos;
	pos += YCameraManager::GetInstance()->GetCameraPos();
	pos += hitActor_.ShakePosValue();

	trfm_.UpdateMatrix({ pos });
	
	sprite_->SetColor(hitActor_.ColorValue());

	sprite_->Update(trfm_.m_);
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
