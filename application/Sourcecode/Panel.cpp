#include "Panel.h"
#include <imgui.h>
#include <string>
#include "Mino.h"
#include "Collision.h"
#include "WinAPI.h"

#pragma region Panel
Panel::Panel()
{
	//配列の数を指定
	maxPanelSize_ = 10;
	initalSize_ = 2;
	//配列初期化
	displayPanel_.resize(maxPanelSize_);
	systemPanel_.resize(maxPanelSize_);
	for (int32_t i = 0; i < maxPanelSize_; i++)
	{
		displayPanel_[i].resize(maxPanelSize_);
		systemPanel_[i].resize(maxPanelSize_);
	}

	for (int32_t y = 0; y < displayPanel_.size(); y++)
	{
		for (int32_t x = 0; x < displayPanel_[y].size(); x++)
		{
			displayPanel_[x][y] = 0;
		}
	}
	//中心からinitalSize_の分、空のパネルを配置する
	int32_t sizeMinY = ((int32_t)(displayPanel_.size() - 1) / 2);
	int32_t sizeMaxY = ((int32_t)(displayPanel_.size() - 1) / 2) + (initalSize_ - 1);

	int32_t sizeMinX = ((int32_t)(displayPanel_[0].size() - 1) / 2);
	int32_t sizeMaxX = ((int32_t)(displayPanel_[0].size() - 1) / 2) + (initalSize_ - 1);

	for (int32_t y = 0; y < displayPanel_.size(); y++)
	{
		for (int32_t x = 0; x < displayPanel_[y].size(); x++)
		{
			if (y >= sizeMinY && y <= sizeMaxY&&
				x >= sizeMinX && x <= sizeMaxX) {
				displayPanel_[x][y] = State::EMPTY;
			}
			systemPanel_[x][y] = displayPanel_[x][y];
		}
	}
	isSetComplete_ = false;
	isAllFill_ = false;
	updateType_ = UpdateType::All;
	//スプライトのサイズ
	spritePos_ = { 
		WinAPI::GetWindowSize().x / 3.4f,
		WinAPI::GetWindowSize().y / 3.f
	};
	spriteSize_ = 32;
	spriteScale_ = 1;
	sprite_ = std::make_unique<PanelSprite>(maxPanelSize_, spritePos_, spriteScale_);
}

void Panel::Update()
{
	if (updateType_ == UpdateType::All)
	{
		Vector2 mPos = MouseInput::GetInstance()->mPos_;
		emptyPanelNum_ = 0;
		for (int32_t y = 0; y < displayPanel_.size(); y++)
		{
			for (int32_t x = 0; x < displayPanel_[y].size(); x++)
			{
				Vector2 leftUp = {
					spritePos_.x + (x * spriteSize_),
					spritePos_.y + (y * spriteSize_),
				};
				Vector2 rightDown = {
					spritePos_.x + ((x + 1) * spriteSize_),
					spritePos_.y + ((y + 1) * spriteSize_),
				};

				Box2D box = {
					leftUp,
					rightDown
				};
				//選択している箇所の数値を変える
				if (CheckBox2DtoPoint(box, mPos))
				{
					selectPos_ = { x,y };
				}
				else if (displayPanel_[x][y] != State::EMPTY)
				{
					displayPanel_[x][y] = systemPanel_[x][y];
				}
				
				if (systemPanel_[x][y] == State::EMPTY) {
					emptyPanelNum_++;
				}
			}
		}

		//エラーが起きないように選択している場所をクランプする
		SelectPosClamp(MinoList::GetMinoList((MinoType)minoType_));
		//左クリックをしたらパネルを設置する
		if (MouseInput::GetInstance()->IsMouseTrigger(MOUSE_LEFT))
		{
			SetPanel(MinoList::GetMinoList((MinoType)minoType_));

			isAllFill_ = true;
			for (int32_t y = 0; y < systemPanel_.size(); y++)
			{
				for (int32_t x = 0; x < systemPanel_[y].size(); x++)
				{
					if (systemPanel_[x][y] == State::EMPTY)
					{
						//空のパネルを見つけたらすべて埋まっているフラグをfalseにする
						isAllFill_ = false;
						break;
					}
				}
			}
		}
		//見た目のパネルの配列を更新
		DisplayPanelUpdate(MinoList::GetMinoList((MinoType)minoType_));

		sprite_->Update(displayPanel_);
	}
	else
	{
		sprite_->Update(displayPanel_);
	}
}

void Panel::DrawSprite()
{
	sprite_->Draw();
}

void Panel::DrawImGui()
{
	ImGui::Begin("Panel");
	//配列表示
	if (ImGui::CollapsingHeader("displayPanel"))
	{
		for (uint32_t y = 0; y < displayPanel_.size(); y++)
		{
			ImGui::Text("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
				displayPanel_[0][y], displayPanel_[1][y], displayPanel_[2][y], displayPanel_[3][y], displayPanel_[4][y],
				displayPanel_[5][y], displayPanel_[6][y], displayPanel_[7][y], displayPanel_[8][y], displayPanel_[9][y]);
		}
	}
	if (ImGui::CollapsingHeader("systemPanel"))
	{
		for (uint32_t y = 0; y < systemPanel_.size(); y++)
		{
			ImGui::Text("%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
				systemPanel_[0][y], systemPanel_[1][y], systemPanel_[2][y], systemPanel_[3][y], systemPanel_[4][y],
				systemPanel_[5][y], systemPanel_[6][y], systemPanel_[7][y], systemPanel_[8][y], systemPanel_[9][y]);
		}
	}
	
	//選択しているパネル場所変更
	ImGui::InputInt("x", (int*)&selectPos_.x);
	ImGui::InputInt("y", (int*)&selectPos_.y);
	//選択しているミノ変更
	std::string typeName;
	static int panelType = 0;
	ImGui::InputInt("type", &panelType);
	panelType = Clamp(panelType,0,6);
	//minoType_ = (MinoType)panelType;

	

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
	
	//選択しているミノを設置
	if (ImGui::Button("SetPanel")) {
		SetPanel(MinoList::GetMinoList((MinoType)panelType));
	}
	//リセット
	if (ImGui::Button("Reset")) {
		PanelReset();
	}
	//次のラウンドに行くための処理をする
	if (ImGui::Button("NextRound")) {
		PanelUpdate();
	}

	ImGui::Text("isAllFill : %d", isAllFill_);
	ImGui::Text("emptyPanelNum : %d", emptyPanelNum_);

	ImGui::End();
}

void Panel::PanelUpdate()
{
	attackPanelNum_ = 0;
	for (uint32_t y = 0; y < displayPanel_.size(); y++)
	{
		for (uint32_t x = 0; x < displayPanel_[y].size(); x++)
		{
			//NEXT_RELEASEを攻撃可能パネルにして攻撃パネルもリセットする
			if (systemPanel_[x][y] == State::NEXT_RELEASE) {
				systemPanel_[x][y] = State::EMPTY;
			}
			else if (systemPanel_[x][y] == State::ATTACK) {
				systemPanel_[x][y] = State::EMPTY;
				//攻撃パネルをカウントする
				attackPanelNum_++;
			}
		}
	}
}

void Panel::PanelReset()
{
	for (uint32_t y = 0; y < displayPanel_.size(); y++)
	{
		for (uint32_t x = 0; x < displayPanel_[y].size(); x++)
		{
			displayPanel_[x][y] = 0;
		}
	}

	uint32_t sizeMinY = ((uint32_t)(displayPanel_.size() - 1) / 2);
	uint32_t sizeMaxY = ((uint32_t)(displayPanel_.size() - 1) / 2) + (initalSize_ - 1);

	uint32_t sizeMinX = ((uint32_t)(displayPanel_[0].size() - 1) / 2);
	uint32_t sizeMaxX = ((uint32_t)(displayPanel_[0].size() - 1) / 2) + (initalSize_ - 1);

	for (uint32_t y = 0; y < displayPanel_.size(); y++)
	{
		for (uint32_t x = 0; x < displayPanel_[y].size(); x++)
		{
			if (y >= sizeMinY && y <= sizeMaxY &&
				x >= sizeMinX && x <= sizeMaxX) {
				displayPanel_[x][y] = State::EMPTY;
			}
			systemPanel_[x][y] = displayPanel_[x][y];
		}
	}
}

bool Panel::IsCanChange(const Mino& mino)
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
			if (systemPanel_[x][y] == State::EMPTY &&
				mino.panel_[panelY][panelX] == 1)
			{
				result = true;
			}
			//NEXT_RELEASEと重なっていたら即falseを返す
			else if (systemPanel_[x][y] == State::NEXT_RELEASE &&
				mino.panel_[panelY][panelX] == 1)
			{
				return false;
			}
			//ATTACKと重なっていたら即falseを返す
			else if (systemPanel_[x][y] == State::ATTACK &&
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

void Panel::DisplayPanelUpdate(const Mino& mino)
{
	for (int32_t y = 0; y < displayPanel_.size(); y++)
	{
		for (int32_t x = 0; x < displayPanel_[y].size(); x++)
		{
			if (displayPanel_[x][y] != State::EMPTY)
			{
				displayPanel_[x][y] = systemPanel_[x][y];
			}
		}
	}

	uint32_t sizeY = selectPos_.y + (uint32_t)mino.panel_.size();
	uint32_t sizeX = selectPos_.x + (uint32_t)mino.panel_[0].size();

	uint32_t panelX = 0;
	uint32_t panelY = 0;

	for (uint32_t y = selectPos_.y; y < sizeY; y++)
	{
		panelX = 0;
		for (uint32_t x = selectPos_.x; x < sizeX; x++)
		{
			bool isSetTempPos =
				systemPanel_[x][y] == State::EMPTY || systemPanel_[x][y] == State::NOT_OPEN;
			//空のパネルに配置したら
			if (isSetTempPos &&
				mino.panel_[panelY][panelX] == 1)
			{
				displayPanel_[x][y] = State::TEMPPOS;
			}

			panelX++;
		}
		panelY++;
	}
}

void Panel::SelectPosClamp(const Mino& mino)
{
	//右端、下端の座標
	uint32_t sizeY = selectPos_.y + (uint32_t)mino.panel_.size() - 1;
	uint32_t sizeX = selectPos_.x + (uint32_t)mino.panel_[0].size() - 1;

	uint32_t panelsizeY = (uint32_t)systemPanel_.size() - 1;
	uint32_t panelsizeX = (uint32_t)systemPanel_[0].size() - 1;
	//比較した値分移動させる
	if (panelsizeY < sizeY) {
		int32_t sub = sizeY - panelsizeY;
		selectPos_.y -= sub;
	}
	if (selectPos_.y < 0) {
		selectPos_.y = Max(selectPos_.y, 0);
	}

	if (panelsizeX < sizeX) {
		int32_t sub = sizeX - panelsizeX;
		selectPos_.x -= sub;
	}
	if (selectPos_.x < 0) {
		selectPos_.x = Max(selectPos_.x, 0);
	}
}

void Panel::SetPanel(const Mino& mino)
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
			if (systemPanel_[x][y] == State::EMPTY &&
				mino.panel_[panelY][panelX] == 1)
			{
				systemPanel_[x][y] = State::ATTACK;
			}
			//開いていないパネルに配置したら
			else if (systemPanel_[x][y] == State::NOT_OPEN &&
				mino.panel_[panelY][panelX] == 1)
			{
				systemPanel_[x][y] = State::NEXT_RELEASE;
			}
			//全て更新する
			displayPanel_[x][y] = systemPanel_[x][y];

			panelX++;
		}
		panelY++;
	}
	isSetComplete_ = true;
}
#pragma endregion

#pragma region PanelSprite
PanelSprite::PanelSprite(uint32_t panelSize, Vector2 basePos, float panelScale)
{
	//配列初期化
	panels_.resize(panelSize);
	for (uint32_t i = 0; i < panelSize; i++)
	{
		panels_[i].resize(panelSize);
	}

	for (uint32_t y = 0; y < panels_.size(); y++)
	{
		for (uint32_t x = 0; x < panels_[y].size(); x++)
		{
			panels_[x][y].sprite_.Ini();
			panels_[x][y].sprite_.SetTexture(TextureManager::GetInstance()->GetTexture("Panel"));

			Vector2 pos = {
				basePos.x + (32.f * panelScale) * x,
				basePos.y + (32.f * panelScale) * y,
			};

			panels_[x][y].sprite_.SetPos(pos);
			panels_[x][y].sprite_.SetScale(Vector2(panelScale, panelScale));
			
			// トランスフォーム
			panels_[x][y].trfm_.Initialize();
			panels_[x][y].trfm_.pos_ = Vector3(pos.x, pos.y, 0.0f);
			
			// アニメーション用
			panels_[x][y].slimeActor_.Initialize(10, { Vector3(), Vector3(0.4f, 0.4f, 0.4f) }, 3.0f);
			panels_[x][y].rotaTim_.Initialize(40);
		}
	}

	rotaEas_.Initialize(0.0f, 3.141592f * 2.0f, 2.0f);
}

void PanelSprite::Update(const std::vector<std::vector<int32_t>>& panel)
{
	for (uint32_t y = 0; y < panels_.size(); y++)
	{
		for (uint32_t x = 0; x < panels_[y].size(); x++)
		{
			//パネルの色変更
			if (panel[x][y] == State::NOT_OPEN) {
				panels_[x][y].sprite_.SetColor(Color(100, 100, 100, 255));
				panels_[x][y].isSet_ = false;
				panels_[x][y].isOpen_ = false;
			}
			else if (panel[x][y] == State::EMPTY) {
				panels_[x][y].sprite_.SetColor(Color(255, 255, 255, 255));
				panels_[x][y].isSet_ = false;
				panels_[x][y].isOpen_ = false;
			}
			else if (panel[x][y] == State::ATTACK) {
				panels_[x][y].sprite_.SetColor(Color(255, 150, 150, 255));
				SetAnimation(x, y);
			}
			else if (panel[x][y] == State::SELECT) {
				panels_[x][y].sprite_.SetColor(Color(0, 255, 0, 255));
			}
			else if (panel[x][y] == State::NEXT_RELEASE) {
				panels_[x][y].sprite_.SetColor(Color(0, 0, 255, 255));
				OpenAnimation(x, y);
			}
			else if (panel[x][y] == State::TEMPPOS) {
				panels_[x][y].sprite_.SetColor(Color(0, 200, 200, 255));
			}

			// アニメーション
			YGame::YTransform::Status animeStatus;

			panels_[x][y].slimeActor_.Update();
			animeStatus.scale_ += panels_[x][y].slimeActor_.WobbleScaleValue(YGame::SlimeActor::EaseType::eOut);
			
			panels_[x][y].rotaTim_.Update();
			animeStatus.rota_.z += rotaEas_.InOut(panels_[x][y].rotaTim_.Ratio());

			// 行列更新
			panels_[x][y].trfm_.UpdateMatrix(animeStatus);
			panels_[x][y].sprite_.Update(panels_[x][y].trfm_.m_);
		}
	}
}

void PanelSprite::SetAnimation(const size_t x, const size_t y)
{
	if (panels_[x][y].isSet_) { return; }
	panels_[x][y].slimeActor_.Wobble();
	panels_[x][y].isSet_ = true;
}

void PanelSprite::OpenAnimation(const size_t x, const size_t y)
{
	if (panels_[x][y].isOpen_) { return; }
	panels_[x][y].slimeActor_.Wobble();
	panels_[x][y].rotaTim_.Reset(true);
	panels_[x][y].isOpen_ = true;
}

void PanelSprite::Draw()
{
	for (uint32_t y = 0; y < panels_.size(); y++)
	{
		for (uint32_t x = 0; x < panels_[y].size(); x++)
		{
			panels_[x][y].sprite_.Draw();
		}
	}
}

#pragma endregion