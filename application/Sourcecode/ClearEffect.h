#pragma once
#include "Sprite.h"
#include "Timer.h"

struct ClearEffectChar {
	std::unique_ptr<Sprite> sprite;
	bool isActive;
	Timer timer;
	Vector2 easeStartPos_;
	Vector2 easeEndPos_;
};

class ClearEffect
{
private:
	std::array<std::unique_ptr<ClearEffectChar>, 8> sprite_;
	Vector2 pos_;
	Timer timer_;
	uint32_t index_;
public:
	ClearEffect();
	void Update();
	void Draw();
};
