#pragma once
#include "Sprite.h"

class Player
{

public:

	void Initialize();

	void Update();

	void Draw();

private:

	std::unique_ptr<Sprite> sprite_ = nullptr;
};

