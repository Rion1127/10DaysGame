#pragma once
#include "Texture.h"
#include <vector>
#include "Sprite.h"
class Number
{
private:
	Texture numTex_;
	int32_t maxDigit_;
	int32_t number_;
	std::vector<int32_t> digit_;
	std::vector<std::unique_ptr<Sprite>> sprite_;
	Vector2 pos_;
	float interval_;
	float scale_;
	//Š„‚èZ‚Ì”’l
	int32_t divisionNum_;
public:
	Number(int32_t maxDigit,Vector2 pos,float scale);
	void Update();
	void Draw();
private:
	void DigitUpdate();
public:
	void SetNumber(int32_t number) { number_ = number; };
};

