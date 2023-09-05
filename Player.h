#pragma once
#include "Sprite.h"

class Player
{

public:

	void Initialize();

	void Update();

	void Draw();
	void DrawImGui();
public:
	void Damage(int32_t damage) { health_ -= damage; }
public:
	int32_t GetAttackPower() { return attackpower_; }
private:
	std::unique_ptr<Sprite> sprite_ = nullptr;
	int32_t health_;
	int32_t attackpower_;
};

