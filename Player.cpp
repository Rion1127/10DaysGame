#include "Player.h"

void Player::Initialize()
{
	sprite_ = std::make_unique<Sprite>();
	sprite_->Ini();
	sprite_->SetTexture(TextureManager::GetInstance()->GetTexture("Player"));
	sprite_->SetPos(Vector2(200, 500));
	sprite_->SetPos(Vector2(200, 500));
}

void Player::Update()
{
	sprite_->Update();
}

void Player::Draw()
{
	sprite_->Draw();
}
