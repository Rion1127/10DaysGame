#pragma once
#include "Sprite.h"

class Enemy
{

public:

	void Initialize();

	void Update();

	void Draw();

private:

	std::unique_ptr<Sprite> sprite_ = nullptr;
};

