#include "Button.h"

Button::Button(Vector2 pos)
{
	sprite_ = std::make_unique<Sprite>();
	sprite_->Ini();
	sprite_->SetTexture(TextureManager::GetInstance()->GetTexture("Panel"));
	sprite_->SetAnchor(Vector2(0.5f, 0.5f));
	pos_ = pos;
	sprite_->SetPos(pos_);
	
	col_.leftUp = {
		pos_.x - (sprite_->GetTexture().size_.x / 2),
		pos_.y - (sprite_->GetTexture().size_.y / 2)
	};
	col_.RightDown = {
		pos_.x + (sprite_->GetTexture().size_.x / 2),
		pos_.y + (sprite_->GetTexture().size_.y / 2)
	};
	sprite_->GetTexture();
}

void Button::Update()
{
	sprite_->SetPos(pos_);
	col_.leftUp = {
		pos_.x - (sprite_->GetTexture().size_.x / 2),
		pos_.y - (sprite_->GetTexture().size_.y / 2)
	};
	col_.RightDown = {
		pos_.x + (sprite_->GetTexture().size_.x / 2),
		pos_.y + (sprite_->GetTexture().size_.y / 2)
	};

	Vector2 mPos = MouseInput::GetInstance()->mPos_;
	if (CheckBox2DtoPoint(col_, mPos))
	{
		isCollision_ = true;
		sprite_->SetColor(Color(0, 0, 0, 255));
	}
	else
	{
		isCollision_ = false;
		sprite_->SetColor(Color(255, 255, 255, 255));
	}

	sprite_->Update();
}

void Button::Draw()
{
	sprite_->Draw();
}

void Button::SetTexture(Texture* texture)
{
	sprite_->SetTexture(texture);
	col_.leftUp = {
		pos_.x - (sprite_->GetTexture().size_.x / 2),
		pos_.y - (sprite_->GetTexture().size_.y / 2)
	};
	col_.RightDown = {
		pos_.x + (sprite_->GetTexture().size_.x / 2),
		pos_.y + (sprite_->GetTexture().size_.y / 2)
	};
}