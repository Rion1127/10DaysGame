#include "Panel.h"
#include <imgui.h>

Panel::Panel()
{
	//配列の数を指定
	maxPanelSize_ = 10;
	initalSize_ = 2;
	//配列初期化
	panel_.resize(maxPanelSize_);
	savePanel_.resize(maxPanelSize_);
	for (uint32_t i = 0; i < maxPanelSize_; i++)
	{
		panel_[i].resize(maxPanelSize_);
		savePanel_[i].resize(maxPanelSize_);
	}

	for (uint32_t y = 0; y < panel_.size(); y++)
	{
		for (uint32_t x = 0; x < panel_[y].size(); x++)
		{
			panel_[x][y] = 0;
		}
	}

	uint32_t sizeMinY = ((uint32_t)(panel_.size() - 1) / 2);
	uint32_t sizeMaxY = ((uint32_t)(panel_.size() - 1) / 2) + (initalSize_ - 1);

	uint32_t sizeMinX = ((uint32_t)(panel_[0].size() - 1) / 2);
	uint32_t sizeMaxX = ((uint32_t)(panel_[0].size() - 1) / 2) + (initalSize_ - 1);

	for (uint32_t y = 0; y < panel_.size(); y++)
	{
		for (uint32_t x = 0; x < panel_[y].size(); x++)
		{
			if (y >= sizeMinY && y <= sizeMaxY&&
				x >= sizeMinX && x <= sizeMaxX) {
				panel_[x][y] = State::EMPTY;
			}
			savePanel_[x][y] = panel_[x][y];
		}
	}
}

void Panel::Update()
{
	for (uint32_t y = 0; y < panel_.size(); y++)
	{
		for (uint32_t x = 0; x < panel_[y].size(); x++)
		{
			//選択している箇所の数値を変える
			if (debugSelectX == x && debugSelectY == y)
			{
				panel_[debugSelectX][debugSelectY] = State::SELECT;
			}
			else if(panel_[x][y] != State::EMPTY)
			{
				panel_[x][y] = savePanel_[x][y];
			}
		}
	}
	
}

void Panel::Draw()
{
}

void Panel::DrawImGui()
{
	ImGui::Begin("Panel");

	for (uint32_t y = 0; y < panel_.size(); y++)
	{
		ImGui::Text("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
			panel_[0][y], panel_[1][y], panel_[2][y], panel_[3][y], panel_[4][y],
			panel_[5][y], panel_[6][y], panel_[7][y], panel_[8][y], panel_[9][y]);
	}
	

	ImGui::InputInt("y", &debugSelectY);
	ImGui::InputInt("x", &debugSelectX);

	ImGui::End();
}

