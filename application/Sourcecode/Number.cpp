#include "Number.h"

Number::Number(int32_t maxDigit, Vector2 pos, float scale)
{
	numTex_ = *TextureManager::GetInstance()->GetTexture("Number");

	pos_ = pos;
	maxDigit_ = maxDigit;
	scale_ = scale;
	interval_ = (numTex_.size_.x / 10.f) * scale;

	digit_.resize(maxDigit_);
	sprite_.resize(maxDigit_);

	divisionNum_ = 1;
	for (uint32_t i = 0; i < sprite_.size(); i++) {
		sprite_[i] = std::make_unique<Sprite>();
		sprite_[i]->Ini();
		sprite_[i]->SetTexture(&numTex_);

		Vector2 pos = {
			pos_.x + (interval_ * i),
			pos_.y
		};
		sprite_[i]->SetPos(pos);
		sprite_[i]->SetTex_Size(Vector2(128,128));
		Vector2 scale = {
			(1.f / 10.f) * scale_,
			1.f * scale_
		};
		sprite_[i]->SetScale(scale);
		sprite_[i]->SetAnchor(Vector2(0, 0));

		digit_[i] = 0;

		divisionNum_ *= 10;
	}
	number_ = 123;
}

void Number::Update()
{
	for (uint32_t i = 0; i < sprite_.size(); i++) {
		Vector2 pos = {
			pos_.x + (interval_ * i),
			pos_.y
		};
		sprite_[i]->SetPos(pos);

		DigitUpdate();


		Vector2 leftTop = {
			digit_[i] * numTex_.size_.x / 10.f,
			0
		};
		sprite_[i]->SetTex_LeftTop(leftTop);

		sprite_[i]->Update();
	}
}

void Number::Draw()
{
	for (auto& sprite : sprite_) {
		sprite->Draw();
	}

	ImGui::Begin("Number");

	float pos[2] = { pos_.x,pos_.y };
	ImGui::DragFloat2("pos", pos);

	pos_ = { pos[0],pos[1] };

	ImGui::DragInt("num", &number_);

	ImGui::End();
}

void Number::DigitUpdate()
{
	int32_t num = number_;
	int32_t divisionNum = divisionNum_;
	digit_.clear();
	for (int32_t i = 0; i < maxDigit_; i++) {
	
		int32_t digit = (num % divisionNum) / (divisionNum / 10);

		digit_.push_back(digit);

		divisionNum /= 10;
	}
}
