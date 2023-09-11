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
	Vector2 scale =  sprite_->GetScale();
	scale *= 0.8f;
	sprite_->SetScale(scale);

	isActive_ = true;
}

void Button::Update()
{
	sprite_->SetPos(pos_);

	colSize_ = {
		sprite_->GetTexture().size_.x * sprite_->GetScale().x,
		sprite_->GetTexture().size_.y * sprite_->GetScale().y,
	};

	col_.leftUp = {
		pos_.x - (colSize_.x / 2),
		pos_.y - (colSize_.y / 2)
	};
	col_.RightDown = {
		pos_.x + (colSize_.x / 2),
		pos_.y + (colSize_.y / 2)
	};

	Vector2 mPos = MouseInput::GetInstance()->mPos_;
	//—LŒø‚ÌŽž
	if (isActive_)
	{
		if (CheckBox2DtoPoint(col_, mPos))
		{
			isCollision_ = true;

			state_ = PipeLineState::Sub;
		}
		else
		{
			isCollision_ = false;

			state_ = PipeLineState::Alpha;
		}
		sprite_->SetColor(Color(255, 255, 255, 255));
	}
	//–³Œø‚ÌŽž
	else
	{
		sprite_->SetColor(Color(100, 100, 100, 255));
	}

	sprite_->Update();
}

void Button::Draw()
{
	PipelineManager::PreDraw("Sprite", TRIANGLELIST, state_);
	sprite_->Draw();
	PipelineManager::PreDraw("Sprite", TRIANGLELIST);
}

void Button::DrawImgui()
{
	sprite_->DrawImGui();
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