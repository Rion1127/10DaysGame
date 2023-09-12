#pragma once
#include "Sprite.h"
#include "Collision.h"
#include "mInput.h"

class Button {
private:
	std::unique_ptr<Sprite> sprite_;
	Vector2 pos_;
	Vector2 spriteLeftPos_;
	Vector2 texSize_;
	bool isAnime_;
	UINT animeMaxCount_;
	UINT animeCount_;
	UINT animeTimer_;
	
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
	void SetisActive(bool flag) { isActive_ = flag; }
	void SetAncorPoint(Vector2 ancor) { sprite_->SetAnchor(ancor); };
	void SetSpriteLeftPos(Vector2 pos) { spriteLeftPos_ = pos; }
	void SetAnime(Vector2 texSize, UINT animeMaxNum,bool isAnime);

};