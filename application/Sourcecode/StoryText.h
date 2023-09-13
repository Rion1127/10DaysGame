#pragma once
#include "Sprite.h"
#include "Button.h"
class StoryText
{
public:
	enum class State {
		Prologue,
		Fighting,
		Epilogue,
		End
	};
	enum class SpeakEnd {
		Yes,
		No,
		Empty,
	};
private:
	std::unique_ptr<Sprite> textsprite_;
	std::unique_ptr<Sprite> framesprite_;
	int32_t turnBackX_;
	Vector2 index_;
	Vector2 pos_;

	State state_;
	bool frameSkip_;
	SpeakEnd speakEnd_;

	std::unique_ptr<Button> yesButton_;
	std::unique_ptr<Button> noButton_;
public:
	StoryText();
	void Updadte();
	void Draw();
public:
	State GetState() { return state_; }
	bool GetFrameSkip() { return frameSkip_; }
public:
	void SetFrameSkip(bool flag) { frameSkip_ = flag; }
};

