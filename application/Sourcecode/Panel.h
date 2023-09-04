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
	//�p�l�������̃^�[���ɂ���
	void PanelUpdate();
private:
	//�p�l�����Z�b�g�ł��邩�m�F����
	bool IsCanChange(Mino mino);
public:
	//�p�l�����Z�b�g����
	void SetPanel(Mino mino);
	void SetSelectPos(Vector2 pos) { selectPos_.x = (uint32_t)pos.x; selectPos_.y = (uint32_t)pos.y;}
};