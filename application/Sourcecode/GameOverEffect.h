#pragma once
#include "Sprite.h"
#include "Timer.h"

struct GameOverChar {
	std::unique_ptr<Sprite> sprite;
	bool isActive;
	Timer timer;
	Vector2 easeStartPos_;
	Vector2 easeEndPos_;
};

class GameOverEffect
{
private:
	std::array<std::unique_ptr<GameOverChar>,7> sprite_;
	Vector2 pos_;
	Timer timer_;
	uint32_t index_;
public:
	GameOverEffect();
	void Update();
	void Draw();
};

