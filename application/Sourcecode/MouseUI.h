#pragma once
#include "Sprite.h"
#include "Timer.h"
class MouseUI
{
private:
	std::unique_ptr<Sprite> sprite_;
	Timer timer_;
	uint32_t index_;
public:
	MouseUI();
	void Update();
	void Draw();
};

