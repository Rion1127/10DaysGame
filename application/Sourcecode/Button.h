#pragma once
#include "Sprite.h"
#include "Collision.h"
#include "mInput.h"

class Button {
private:
	std::unique_ptr<Sprite> sprite_;
	Vector2 pos_;
	
	Box2D col_;
	bool isCollision_;
	PipeLineState state_;
public:
	Button(Vector2 pos);

	void Update();
	void Draw();
public:
	bool GetIsCollision() { return isCollision_; }
public:
	void SetTexture(Texture* texture);
	void SetPos(Vector2 pos) { pos_ = pos; }
};