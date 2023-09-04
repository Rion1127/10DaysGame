#pragma once
#include <vector>
#include <array>
#include "Mino.h"
#include "Vector2.h"
#include "mInput.h"
#include "Sprite.h"

enum State {
	NOT_OPEN,
	EMPTY,
	ATTACK,
	NEXT_RELEASE,
	SELECT
};

class PanelSprite {
private:
	std::vector<std::vector<Sprite>> sprite_;
public:
	PanelSprite(uint32_t panelSize,Vector2 basePos, float panelScale);

	void Update(const std::vector<std::vector<int32_t>>& panel);
	void Draw();
};

class Panel
{
private:
	
	struct SelectPos {
		int32_t x;
		int32_t y;
	};
private:
	std::vector<std::vector<int32_t>> panel_;
	std::vector<std::vector<int32_t>> savePanel_;
	int32_t maxPanelSize_;
	int32_t initalSize_;

	SelectPos selectPos_;

	Vector2 spritePos_;
	std::unique_ptr<PanelSprite> sprite_;
public:
	Panel();
	void Update();
	void DrawSprite();

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
	void SetSelectPos(Vector2 pos) { selectPos_.x = (int32_t)pos.x; selectPos_.y = (int32_t)pos.y;}
};