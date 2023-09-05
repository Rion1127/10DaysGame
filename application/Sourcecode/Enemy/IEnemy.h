#pragma once
#include "Vector2.h"
#include "Sprite.h"

class IEnemy
{
protected:
	std::unique_ptr<Sprite> sprite_ = nullptr;

	int32_t health_;
public:
	IEnemy(int32_t health);
	virtual void Update() = 0;
	virtual void Draw() = 0;
public:
	void Damage(int32_t health) { health_ -= health; }
};

