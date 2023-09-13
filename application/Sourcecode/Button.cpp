#include "Button.h"
#include <imgui.h>

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

	Vector2 scale = sprite_->GetScale();
	scale *= 0.8f;
	sprite_->SetScale(scale);

	isActive_ = true;
	animeCount_ = 0;
	animeTimer_ = 0;
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

	if (CheckBox2DtoPoint(col_, mPos) && isAnime_ == false)
	{
		isCollision_ = true;

		state_ = PipeLineState::Sub;

	}
	else if(CheckBox2DtoPoint(col_, mPos) && isAnime_ == true)
	{
		animeTimer_++;

		if(animeTimer_ >= 20)
		{
			animeTimer_ = 0;
			if(animeCount_ < animeMaxCount_)
			{
				animeCount_++;
			}
			else
			{
				animeCount_ = 0;
			}

			Vector2 result;
			result.x = texSize_.x * animeCount_;
			result.y = 0.0f;

			sprite_->SetTex_LeftTop(result);
		}

		
		isCollision_ = true;

		state_ = PipeLineState::Alpha;
	}
	else
	{
		isCollision_ = false;

		state_ = PipeLineState::Alpha;
	}

	//—LŒø‚ÌŽž
	if (isActive_)
	{
		sprite_->SetColor(Color(255, 255, 255, 255));
	}
	//–³Œø‚ÌŽž
	else
	{
		isCollision_ = false;
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

void Button::SetAnime(Vector2 texSize, UINT animeMaxNum,bool isAnime)
{
	pos_ = { 450.0f,600.0f };
	sprite_->SetPos(pos_);

	col_.leftUp = {
		pos_.x - (sprite_->GetTexture().size_.x / 2),
		pos_.y - (sprite_->GetTexture().size_.y / 2)
	};
	col_.RightDown = {
		pos_.x + (sprite_->GetTexture().size_.x / 2),
		pos_.y + (sprite_->GetTexture().size_.y / 2)
	};

	isAnime_ = true;
	texSize_ = texSize;

	sprite_->SetTex_LeftTop({});
	sprite_->SetTex_Size(Vector2(300.0f, 200.0f));
	sprite_->SetScale(Vector2(1.0f / 7.0f, 1.0f));

	
	animeMaxCount_ = animeMaxNum;
	
}
