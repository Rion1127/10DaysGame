#include "Panel.h"
#include <imgui.h>
#include <string>
#include "Mino.h"

#pragma region Panel
Panel::Panel()
{
	//配列の数を指定
	maxPanelSize_ = 10;
	initalSize_ = 2;
	//配列初期化
	panel_.resize(maxPanelSize_);
	savePanel_.resize(maxPanelSize_);
	for (int32_t i = 0; i < maxPanelSize_; i++)
	{
		panel_[i].resize(maxPanelSize_);
		savePanel_[i].resize(maxPanelSize_);
	}

	for (int32_t y = 0; y < panel_.size(); y++)
	{
		for (int32_t x = 0; x < panel_[y].size(); x++)
		{
			panel_[x][y] = 0;
		}
	}
	//中心からinitalSize_の分、空のパネルを配置する
	int32_t sizeMinY = ((int32_t)(panel_.size() - 1) / 2);
	int32_t sizeMaxY = ((int32_t)(panel_.size() - 1) / 2) + (initalSize_ - 1);

	int32_t sizeMinX = ((int32_t)(panel_[0].size() - 1) / 2);
	int32_t sizeMaxX = ((int32_t)(panel_[0].size() - 1) / 2) + (initalSize_ - 1);

	for (int32_t y = 0; y < panel_.size(); y++)
	{
		for (int32_t x = 0; x < panel_[y].size(); x++)
		{
			if (y >= sizeMinY && y <= sizeMaxY&&
				x >= sizeMinX && x <= sizeMaxX) {
				panel_[x][y] = State::EMPTY;
			}
			savePanel_[x][y] = panel_[x][y];
		}
	}
	spritePos_ = { 500,200 };
	sprite_ = std::make_unique<PanelSprite>(maxPanelSize_, spritePos_,1.f);
}

void Panel::Update()
{
	selectPos_ = {
		Clamp(selectPos_.x,(int32_t)0,(int32_t)(maxPanelSize_ - 1)),
		Clamp(selectPos_.y,(int32_t)0,(int32_t)(maxPanelSize_ - 1)),
	};


	for (int32_t y = 0; y < panel_.size(); y++)
	{
		for (int32_t x = 0; x < panel_[y].size(); x++)
		{
			//選択している箇所の数値を変える
			if (selectPos_.x == x && selectPos_.y == y)
			{
				panel_[selectPos_.x][selectPos_.y] = State::SELECT;
			}
			else if(panel_[x][y] != State::EMPTY)
			{
				panel_[x][y] = savePanel_[x][y];
			}
		}
	}
	
	sprite_->Update(panel_);
}

void Panel::DrawSprite()
{
	sprite_->Draw();
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
	

	ImGui::InputInt("x", (int*)&selectPos_.x);
	ImGui::InputInt("y", (int*)&selectPos_.y);

	std::string typeName;
	static int panelType = 0;
	ImGui::InputInt("type", &panelType);

	if (panelType == 0) {
		typeName = "Omino";
	}
	else if (panelType == 1) {
		typeName = "Tmino";
	}
	else if (panelType == 2) {
		typeName = "Smino";
	}
	else if (panelType == 3) {
		typeName = "Zmino";
	}
	else if (panelType == 4) {
		typeName = "Imino";
	}
	else if (panelType == 5) {
		typeName = "Lmino";
	}
	else if (panelType == 6) {
		typeName = "Jmino";
	}

	ImGui::Text(typeName.c_str());
	

	if (ImGui::Button("SetPanel")) {
		SetPanel(MinoList::GetMinoList((Type)panelType));
	}

	if (ImGui::Button("Reset")) {
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
				if (y >= sizeMinY && y <= sizeMaxY &&
					x >= sizeMinX && x <= sizeMaxX) {
					panel_[x][y] = State::EMPTY;
				}
				savePanel_[x][y] = panel_[x][y];
			}
		}
	}

	if (ImGui::Button("NextRound")) {
		PanelUpdate();
	}

	ImGui::End();
}

void Panel::PanelUpdate()
{
	for (uint32_t y = 0; y < panel_.size(); y++)
	{
		for (uint32_t x = 0; x < panel_[y].size(); x++)
		{
			//NEXT_RELEASEを攻撃可能パネルにして攻撃パネルもリセットする
			if (savePanel_[x][y] == State::NEXT_RELEASE) {
				savePanel_[x][y] = State::EMPTY;
			}
			else if (savePanel_[x][y] == State::ATTACK) {
				savePanel_[x][y] = State::EMPTY;
			}
		}
	}
}

bool Panel::IsCanChange(Mino mino)
{
	bool result = false;
	uint32_t sizeY = selectPos_.y + (uint32_t)mino.panel_.size();
	uint32_t sizeX = selectPos_.x + (uint32_t)mino.panel_[0].size();

	uint32_t panelX = 0;
	uint32_t panelY = 0;

	for (uint32_t y = selectPos_.y; y < sizeY; y++)
	{
		panelX = 0;
		for (uint32_t x = selectPos_.x; x < sizeX; x++)
		{
			//空のパネルと重なっていたら
			if (savePanel_[x][y] == State::EMPTY &&
				mino.panel_[panelY][panelX] == 1)
			{
				result = true;
			}
			//NEXT_RELEASEと重なっていたら即falseを返す
			else if (savePanel_[x][y] == State::NEXT_RELEASE &&
				mino.panel_[panelY][panelX] == 1)
			{
				return false;
			}
			//ATTACKと重なっていたら即falseを返す
			else if (savePanel_[x][y] == State::ATTACK &&
				mino.panel_[panelY][panelX] == 1)
			{
				return false;
			}

			panelX++;
		}
		panelY++;
	}


	return result;
}

void Panel::SetPanel(Mino mino)
{
	if (IsCanChange(mino) == false) return;

	uint32_t sizeY = selectPos_.y + (uint32_t)mino.panel_.size();
	uint32_t sizeX = selectPos_.x + (uint32_t)mino.panel_[0].size();

	uint32_t panelX = 0;
	uint32_t panelY = 0;

	for (uint32_t y = selectPos_.y; y < sizeY; y++)
	{
		panelX = 0;
		for (uint32_t x = selectPos_.x; x < sizeX; x++)
		{
			//空のパネルに配置したら
			if (savePanel_[x][y] == State::EMPTY &&
				mino.panel_[panelY][panelX] == 1)
			{
				savePanel_[x][y] = State::ATTACK;
			}
			//開いていないパネルに配置したら
			else if (savePanel_[x][y] == State::NOT_OPEN &&
				mino.panel_[panelY][panelX] == 1)
			{
				savePanel_[x][y] = State::NEXT_RELEASE;
			}
			//全て更新する
			panel_[x][y] = savePanel_[x][y];

			panelX++;
		}
		panelY++;
	}
}
#pragma endregion

#pragma region PanelSprite
PanelSprite::PanelSprite(uint32_t panelSize, Vector2 basePos, float panelScale)
{
	//配列初期化
	sprite_.resize(panelSize);
	for (uint32_t i = 0; i < panelSize; i++)
	{
		sprite_[i].resize(panelSize);
	}

	for (uint32_t y = 0; y < sprite_.size(); y++)
	{
		for (uint32_t x = 0; x < sprite_[y].size(); x++)
		{
			sprite_[x][y].Ini();
			sprite_[x][y].SetTexture(TextureManager::GetInstance()->GetTexture("Panel"));

			Vector2 pos = {
				basePos.x + (32.f * panelScale) * x,
				basePos.y + (32.f * panelScale) * y,
			};

			sprite_[x][y].SetPos(pos);
			sprite_[x][y].SetScale(Vector2(panelScale, panelScale));
		}
	}
}

void PanelSprite::Update(const std::vector<std::vector<int32_t>>& panel)
{
	for (uint32_t y = 0; y < sprite_.size(); y++)
	{
		for (uint32_t x = 0; x < sprite_[y].size(); x++)
		{
			if (panel[x][y] == State::NOT_OPEN) {
				sprite_[x][y].SetColor(Color(100,100,100,255));
			}
			else if (panel[x][y] == State::EMPTY) {
				sprite_[x][y].SetColor(Color(255, 255, 255, 255));
			}
			else if (panel[x][y] == State::ATTACK) {
				sprite_[x][y].SetColor(Color(255, 150, 150, 255));
			}
			else if (panel[x][y] == State::SELECT) {
				sprite_[x][y].SetColor(Color(0, 255, 0, 255));
			}
			else if (panel[x][y] == State::NEXT_RELEASE) {
				sprite_[x][y].SetColor(Color(0, 0, 255, 255));
			}


			sprite_[x][y].Update();
		}
	}
}

void PanelSprite::Draw()
{
	for (uint32_t y = 0; y < sprite_.size(); y++)
	{
		for (uint32_t x = 0; x < sprite_[y].size(); x++)
		{

			sprite_[x][y].Draw();
		}
	}
}

#pragma endregion