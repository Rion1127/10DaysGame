#include "Player.h"
#include "YCameraManager.h"
#include <imgui.h>
#include "WinAPI.h"

void Player::Initialize()
{	
	Vector3 pos = {
		WinAPI::GetWindowSize().x / 2.0f - 128.0f,
		WinAPI::GetWindowSize().y / 6.0f + 8.0f,
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
	recovery_.Initialize({ {0.0f,-64.0f,0.0f},{},{0.5f,0.5f,1.0f} }, &trfm_.m_, 0);

	drawer_.MoveAnimation();

	statusTrfm_.Initialize();
	statusTrfm_.pos_ = Vector3(90, 500, 0);

	statusFrame_.Ini("statusframe");
	statusFrame_.SetTexture(TextureManager::GetInstance()->GetTexture("StatusFrame"));
	for (size_t i = 0; i < status_.size(); i++)
	{
		YGame::YTransform::Status status = YGame::YTransform::Status::Default();
		
		status.pos_ = { statusFrame_.GetPos().x,statusFrame_.GetPos().y,0.0f };
		status.pos_.x += 32.0f;
		status.pos_.y += (i * 36.0f) + 4.0f;

		status.scale_ = { 0.25f,0.25f,1.0f };

		status_[i].Initialize(status, &statusTrfm_.m_);
	}

	status_[0].PowerUpAnimation(baseAttackpower_);
	status_[1].PowerUpAnimation(luck_);
}

void Player::Update()
{	
	trfm_.UpdateMatrix({ YGame::YCameraManager::GetInstance()->GetCameraPos(), {}, {} });

	if (health_ <= 0) {
		isAlive_ = false;
	}
	
	drawer_.Update();
	sword_.Update();
	hpBar_.Update();
	damage_.Update();
	recovery_.Update();

	statusTrfm_.UpdateMatrix();
	statusFrame_.Update(statusTrfm_.m_);
	for (size_t i = 0; i < status_.size(); i++)
	{
		status_[i].Update();
	}
}

void Player::StatusUpdate(const int32_t plusHealth, const int32_t plusLuck, const int32_t plusRecover, const int32_t plusAttack)
{
	status_[0].PlusAnimation(plusAttack);
	status_[1].PlusAnimation(plusLuck);
	//status_[2].PlusAnimation();
	//status_[3].PlusAnimation();
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
	recovery_.Draw();
	statusFrame_.Draw();
	for (size_t i = 0; i < status_.size(); i++)
	{
		status_[i].Draw();
	}
}

void Player::DrawImGui()
{
	ImGui::Begin("player");
	//ImGui::Text("HP : %d", health_);
	ImGui::Text("power : %d", baseAttackpower_);
	ImGui::End();

	statusFrame_.DrawImGui();
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

	if (hpBar_.MaxHP() <= health_)
	{
		hpBar_.ChangeMaxHPAnimation(health_);
	}
	hpBar_.ChangeHPAnimation(health_);

	if (0 < health)
	{
		recovery_.SetNumber(health);
		recovery_.RecoverAnimation();
	}
}

void Player::AddHealth(int32_t health) {
	health_ += health;
}

void Player::AddAttack(int32_t attack) {
	baseAttackpower_ += attack;
	status_[0].PowerUpAnimation(baseAttackpower_);
}

void Player::AddLuck(int32_t luck) {
	luck_ += luck;
	status_[1].PowerUpAnimation(luck_);
}

void Player::IdleAnimation()
{
	drawer_.IdleAnimation();
}

void Player::MoveAnimation()
{
	drawer_.MoveAnimation();
}
