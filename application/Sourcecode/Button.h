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
	Vector2 colSize_;
	bool isActive_;
public:
	Button(Vector2 pos);

	void Update();
	void Draw();
	void DrawImgui();
public:
	bool GetIsCollision() { return isCollision_; }
public:
	void SetTexture(Texture* texture);
	void SetPos(Vector2 pos) { pos_ = pos; }
};