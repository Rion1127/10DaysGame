#pragma once
#include "Sprite.h"
#include "Collision.h"
#include "mInput.h"
#include "Timer.h"
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
	UINT animeFrame_;
	
	Box2D col_;
	bool isCollision_;
	PipeLineState state_;
	Vector2 colSize_;
	bool isActive_;

	bool isAnimation_;			//アニメーションフラグ
	bool isActiveAnimation_;	//アニメーションをさせるか
	Timer timer_;
public:
	Button(Vector2 pos);

	void Update();
	void Draw();
	void DrawImgui();

	void SetAnime(Vector2 texSize, UINT animeMaxNum, bool isAnime, UINT animeFrame);
public:
	bool GetIsCollision() { return isCollision_; }
public:
	void SetTexture(Texture* texture);
	void SetPos(Vector2 pos) { pos_ = pos; }
	void SetisActive(bool flag) { isActive_ = flag; }
	void SetAncorPoint(Vector2 ancor) { sprite_->SetAnchor(ancor); };
	void SetIsActiveAnimation(bool flag) { isActiveAnimation_ = flag; }
	Sprite* GetSprite() { return sprite_.get(); }
};