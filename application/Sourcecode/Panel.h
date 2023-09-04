#pragma once
#include <vector>
#include <array>
#include "Mino.h"
#include "Vector2.h"
#include "mInput.h"
#include "Sprite.h"

class PanelSprite {
private:
	std::vector<std::vector<Sprite>> sprite_;
public:
	PanelSprite(uint32_t panelSize);

	void Update();
	void Draw();
};

class Panel
{
private:
	enum State {
		NOT_OPEN,
		EMPTY,
		ATTACK,
		NEXT_RELEASE,
		SELECT
	};
	struct SelectPos {
		uint32_t x;
		uint32_t y;
	};
private:
	std::vector<std::vector<uint32_t>> panel_;
	std::vector<std::vector<uint32_t>> savePanel_;
	uint32_t maxPanelSize_;
	uint32_t initalSize_;

	SelectPos selectPos_;

public:
	Panel();
	void Update();
	void Draw();

	void DrawImGui();
public:
	//パネルを次のターンにする
	void PanelUpdate();
private:
	//パネルをセットできるか確認する
	bool IsCanChange(Mino mino);
public:
	//パネルをセットする
	void SetPanel(Mino mino);
	void SetSelectPos(Vector2 pos) { selectPos_.x = (uint32_t)pos.x; selectPos_.y = (uint32_t)pos.y;}
};