#include "GameOverEffect.h"
#include "WinAPI.h"
#include "Easing.h"

GameOverEffect::GameOverEffect()
{
	pos_ = { WinAPI::GetWindowSize().x / 2.f - 192.f,300 };
	
	for (uint32_t i = 0; i < sprite_.size(); i++) {
		sprite_[i] = std::make_unique<GameOverChar>();
		sprite_[i]->sprite = std::make_unique<Sprite>();
		sprite_[i]->sprite->Ini();
		sprite_[i]->sprite->SetTexture(TextureManager::GetInstance()->GetTexture("GameOver"));
		sprite_[i]->sprite->SetTex_Size(Vector2(64.f, 64.f));
		sprite_[i]->sprite->SetScale(Vector2(7.f /64.f,1));
		sprite_[i]->sprite->SetTex_LeftTop(Vector2(64.f * (float)i, 1));

		sprite_[i]->easeEndPos_ = {
			pos_.x + i * 64,
			pos_.y
		};
		sprite_[i]->easeStartPos_ = {
			pos_.x + i * 64,
			pos_.y - 128.f,
		};
		sprite_[i]->sprite->SetPos(sprite_[i]->easeStartPos_);
		sprite_[i]->sprite->Update();
		sprite_[i]->isActive = false;
		sprite_[i]->timer.SetLimitTime(120);
		sprite_[i]->sprite->SetColor(Color(255, 255, 255, 0));
	}

	timer_.SetLimitTime(20);
	index_ = 0;
}

void GameOverEffect::Update()
{
	timer_.AddTime(1);

	if (timer_.GetIsEnd()) {
		sprite_[index_]->isActive = true;
		index_++;
		index_ = Min(index_, (uint32_t)sprite_.size() - 1);
		timer_.Reset();
	}

	for (uint32_t i = 0; i < sprite_.size(); i++) {

		if (sprite_[i]->isActive) {
			sprite_[i]->timer.AddTime(1);

			Vector2 start = sprite_[i]->easeStartPos_;
			Vector2 end = sprite_[i]->easeEndPos_;
			float rate = sprite_[i]->timer.GetTimeRate();

			Vector2 pos = {
				Easing::Cubic::easeOut(start.x,end.x,rate),
				Easing::Cubic::easeOut(start.y,end.y,rate),
			};

			sprite_[i]->sprite->SetPos(pos);

			Color color = sprite_[i]->sprite->GetColor();

			color.a = 255.f * sprite_[i]->timer.GetTimeRate();

			sprite_[i]->sprite->SetColor(color);
		}

		sprite_[i]->sprite->Update();
	}
}

void GameOverEffect::Draw()
{
	for (uint32_t i = 0; i < sprite_.size(); i++) {
		sprite_[i]->sprite->Draw();
	}
}
