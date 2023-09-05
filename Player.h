#pragma once
#include "Sprite.h"

class Player
{

public:

	void Initialize();

	void Update();

	void Draw();
public:
	void Damage(int32_t damage) { health_ -= damage; }
private:
	std::unique_ptr<Sprite> sprite_ = nullptr;
	int32_t health_;
};

