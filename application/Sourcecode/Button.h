#pragma once
#include "Sprite.h"
#include "Collision.h"
#include "mInput.h"

class Button {
private:
	std::unique_ptr<Sprite> sprite_;
	Vector2 pos_;
	//クリックしたときに返す値
	int32_t return_;
	Box2D col_;
	bool isCollision_;
public:
	Button(Vector2 pos, int32_t returnValue);

	void Update();
	void Draw();
public:
	bool GetIsCollision() { return isCollision_; }
public:
	void SetTexture(Texture* texture);
};