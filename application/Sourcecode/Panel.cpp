#include "Panel.h"
#include <imgui.h>

Panel::Panel()
{
	maxPanelSize_ = 10;
	panel_.resize(maxPanelSize_);
	for (uint32_t i = 0; i < maxPanelSize_; i++)
	{
		panel_[i].resize(maxPanelSize_);
	}

	for (uint32_t y = 0; y < panel_.size(); y++)
	{
		for (uint32_t x = 0; x < panel_[y].size(); x++)
		{
			panel_[x][y] = 0;
		}
	}
}

void Panel::Update()
{
	for (uint32_t y = 0; y < panel_.size(); y++)
	{
		for (uint32_t x = 0; x < panel_[y].size(); x++)
		{
			//‘I‘ð‚µ‚Ä‚¢‚é‰ÓŠ‚Ì”’l‚ð•Ï‚¦‚é
			if (debugSelectX == x && debugSelectY == y)
			{
				panel_[debugSelectX][debugSelectY] = State::SELECT;
			}
			else
			{
				panel_[x][y] = 0;
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

Mino::Mino()
{
}

void Mino::OminoInit()
{
}

void Mino::TminoInit()
{
}

void Mino::SminoInit()
{
}

void Mino::ZminoInit()
{
}

void Mino::IminoInit()
{
}

void Mino::LminoInit()
{
}

void Mino::JminoInit()
{
}
