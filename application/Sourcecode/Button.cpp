#include "Button.h"
#include <imgui.h>
#include "myMath.h"

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

	timer_.SetLimitTime(90);
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
		if (isCollision_ == false)
		{
			if (isAnimation_ == false)
			{
				isAnimation_ = true;
			}
			isCollision_ = true;
		}

		state_ = PipeLineState::Sub;

	}
	else if(CheckBox2DtoPoint(col_, mPos) && isAnime_ == true)
	{
		if(isCollision_ == false)
		{
			if(isAnimation_ == false)
			{
				isAnimation_ = true;
			}
			isCollision_ = true;
		}

		animeTimer_++;

		if(animeTimer_ >= animeFrame_)
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

		state_ = PipeLineState::Alpha;
	}
	else
	{
		isCollision_ = false;

		if(isCollision_ == false)
		{
			animeCount_ = 0;

			Vector2 result;
			result.x = texSize_.x * animeCount_;
			result.y = 0.0f;

			sprite_->SetTex_LeftTop(result);

		}

		state_ = PipeLineState::Alpha;
	}

	//有効の時
	if (isActive_)
	{
		sprite_->SetColor(Color(255, 255, 255, 255));
	}
	//無効の時
	else
	{
		isCollision_ = false;
		sprite_->SetColor(Color(100, 100, 100, 255));
	}
	//アニメーションをさせる
	if (isActiveAnimation_)
	{
		sprite_->SetAnchor(Vector2(0.5f, 0.1f));
		if (isAnimation_)
		{
			timer_.AddTime(1);
			
			float rot = 0;

			float rate = 1.f - timer_.GetTimeRate();
			rot = UpAndDown(50, Radian(45) * rate, (float)timer_.GetTimer());

			sprite_->SetRot(rot);

			if (timer_.GetIsEnd())
			{
				isAnimation_ = false;
				timer_.Reset();
			}
		}
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

void Button::SetAnime(Vector2 texSize, UINT animeMaxNum,bool isAnime, UINT animeFrame)
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

	isAnime_ = true;
	texSize_ = texSize;
	animeFrame_ = animeFrame;

	sprite_->SetTex_LeftTop({});
	sprite_->SetTex_Size(texSize_);
	sprite_->SetScale(Vector2(1.0f / animeMaxNum, 1.0f));

	
	animeMaxCount_ = animeMaxNum;
	
}
