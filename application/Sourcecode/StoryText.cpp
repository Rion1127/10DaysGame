#include "StoryText.h"
#include "WinAPI.h"
#include "mInput.h"
#include "mSound.h"

StoryText::StoryText()
{
	turnBackX_ = 6;

	pos_ = {
		WinAPI::GetWindowSize().x / 2.f,
		660.f
	};

	textsprite_ = std::make_unique<Sprite>();
	textsprite_->Ini();
	textsprite_->SetTexture(TextureManager::GetInstance()->GetTexture("Story"));
	textsprite_->SetTex_Size(Vector2(320, 128));
	Vector2 scale = {
		1.f / 6.f,
		1.f / 4.f
	};
	textsprite_->SetScale(scale);
	textsprite_->SetPos(pos_);

	framesprite_ = std::make_unique<Sprite>();
	framesprite_->Ini();
	framesprite_->SetTexture(TextureManager::GetInstance()->GetTexture("TextFrame"));
	framesprite_->SetPos(pos_);

	state_ = State::Prologue;

	Vector2 yesPos = {
		WinAPI::GetWindowSize().x / 2.f,
		WinAPI::GetWindowSize().y / 2.f,
	};
	yesButton_ = std::make_unique<Button>(yesPos);
	yesButton_->SetTexture(TextureManager::GetInstance()->GetTexture("YesButton"));
	yesButton_->Update();

	Vector2 noPos = {
		WinAPI::GetWindowSize().x / 2.f,
		WinAPI::GetWindowSize().y / 1.7f,
	};
	noButton_ = std::make_unique<Button>(noPos);
	noButton_->SetTexture(TextureManager::GetInstance()->GetTexture("NoButton"));
	noButton_->Update();

	speakEnd_ = SpeakEnd::Empty;
}

void StoryText::Updadte()
{
	if (state_ != State::Fighting)
	{
		//‚Í‚¢or‚¢‚¢‚¦
		if (index_.x == 1 && index_.y == 2)
		{
			if (MouseInput::GetInstance()->IsMouseTrigger(MOUSE_LEFT))
			{
				if (yesButton_->GetIsCollision())
				{
					index_.x = 3;
					index_.y = 2;
					speakEnd_ = SpeakEnd::Yes;
				}
				if (noButton_->GetIsCollision())
				{
					index_.x = 2;
					index_.y = 2;
					speakEnd_ = SpeakEnd::No;
				}
			}
			yesButton_->Update();
			noButton_->Update();
		}
		else
		{
			if (MouseInput::GetInstance()->IsMouseTrigger(MOUSE_LEFT))
			{
				index_.x++;
				if (index_.x > 5)
				{
					index_.y++;
					index_.x = 0;
				}
				SoundManager::Play("Click_2SE", false, 1.0f);

				if (speakEnd_ == SpeakEnd::Yes)
				{

				}
				else if (speakEnd_ == SpeakEnd::No)
				{
					index_.x = 0;
					index_.y = 2;
					speakEnd_ = SpeakEnd::Empty;
				}
			}
		}

		if (index_.x == 4 && index_.y == 2)
		{
			state_ = State::Fighting;
			frameSkip_ = true;
		}
	}

	Vector2 leftTop = {
		index_.x * 320,
		index_.y * 128
	};
	textsprite_->SetTex_LeftTop(leftTop);


	textsprite_->Update();
	framesprite_->Update();
}

void StoryText::Draw()
{
	if (index_.x == 1 && index_.y == 2)
	{
	}else
	if (state_ == State::Prologue ||
		state_ == State::Epilogue)
	{
		framesprite_->Draw();
		textsprite_->Draw();
	}

	if (index_.x == 1 && index_.y == 2)
	{
		yesButton_->Draw();
		noButton_->Draw();
	}
}
