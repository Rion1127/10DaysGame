#include "MouseUI.h"
#include "mInput.h"

MouseUI::MouseUI()
{
	sprite_ = std::make_unique<Sprite>();
	sprite_->Ini("mouseUI");
	sprite_->SetTexture(TextureManager::GetInstance()->GetTexture("Mouse"));
	sprite_->SetTex_Size(Vector2(160,128));
	float scaleX = (1.f / 3.f) * 0.8f;
	sprite_->SetScale(Vector2(scaleX, 0.8f));
	sprite_->SetPos(Vector2(100, 660));
	timer_.SetLimitTime(5);
}

void MouseUI::Update()
{
	timer_.AddTime(1);

	if (timer_.GetIsEnd()) {
		index_ = 0;
	}

	if (MouseInput::GetInstance()->IsMouseTrigger(MOUSE_LEFT)) {
		timer_.Reset();
		index_ = 1;
	}
	else if (MouseInput::GetInstance()->IsMouseTrigger(MOUSE_RIGHT)) {
		timer_.Reset();
		index_ = 2;
	}
	Vector2 leftUpPos = {
		(sprite_->GetTexture().size_.x / 3.f) * (float)index_,
		0
	};

	sprite_->SetTex_LeftTop(leftUpPos);

	sprite_->Update();
}

void MouseUI::Draw()
{
	sprite_->Draw();
	//sprite_->DrawImGui();
}
