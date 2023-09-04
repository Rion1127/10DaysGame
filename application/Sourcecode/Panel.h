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
	//�p�l�������̃^�[���ɂ���
	void PanelUpdate();
private:
	//�p�l�����Z�b�g�ł��邩�m�F����
	bool IsCanChange(Mino mino);
public:
	//�p�l�����Z�b�g����
	void SetPanel(Mino mino);
};