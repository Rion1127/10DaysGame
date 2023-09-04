#pragma once
#include <vector>
#include <array>
#include "Mino.h"
#include "Vector2.h"
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
		int x;
		int y;
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
};