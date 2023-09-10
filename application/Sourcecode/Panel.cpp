#include "Panel.h"
#include <imgui.h>
#include <string>
#include "Mino.h"
#include "Collision.h"
#include "WinAPI.h"
#include "RRandom.h"
#include "mSound.h"

#pragma region Panel
Panel::Panel()
{
	//�z��̐����w��
	maxPanelSize_ = 10;
	initalSize_ = 2;
	//�z�񏉊���
	displayPanel_.resize(maxPanelSize_);
	systemPanel_.resize(maxPanelSize_);
	for (int32_t i = 0; i < maxPanelSize_; i++)
	{
		displayPanel_[i].resize(maxPanelSize_);
		systemPanel_[i].resize(maxPanelSize_);
	}
	//�p�l����������Ԃɂ���
	PanelReset();

	isSetComplete_ = false;
	isAllFill_ = false;
	isPanelReset_ = false;
	updateType_ = UpdateType::All;
	spriteSize_ = 32;
	spriteScale_ = 1;
	//�X�v���C�g�̃T�C�Y
	spritePos_ = {
		WinAPI::GetWindowSize().x / 2.f - ((displayPanel_.size() / 2)) * spriteSize_ + 16.f,
		WinAPI::GetWindowSize().y / 2.f - ((displayPanel_[0].size() / 2) - 2) * spriteSize_
	};

	sprite_ = std::make_unique<PanelSprite>(maxPanelSize_, spritePos_, spriteScale_);

	rotNum_ = 0;

	allPanelSize_.leftUp = spritePos_;
	allPanelSize_.RightDown = {
		spritePos_.x + displayPanel_[0].size() * spriteSize_,
		spritePos_.y + displayPanel_[0].size() * spriteSize_
	};
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
				//�I�����Ă���ӏ��̐��l��ς���
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
		if (MouseInput::GetInstance()->IsMouseTrigger(MOUSE_RIGHT))
		{
			SoundManager::Play("RotSE", false, 1.0f);
			rotNum_++;
			if (rotNum_ > 3)rotNum_ = 0;
		}
		nowMino_ = SetRotMino(MinoList::GetMinoList((MinoType)minoType_));
		//�G���[���N���Ȃ��悤�ɑI�����Ă���ꏊ���N�����v����
		SelectPosClamp(nowMino_);
		//���N���b�N��������p�l����ݒu����
		if (MouseInput::GetInstance()->IsMouseTrigger(MOUSE_LEFT))
		{
			if (CheckBox2DtoPoint(allPanelSize_, mPos)) {
				SetPanel(nowMino_);

				isAllFill_ = true;
				for (int32_t y = 0; y < systemPanel_.size(); y++)
				{
					for (int32_t x = 0; x < systemPanel_[y].size(); x++)
					{
						if (systemPanel_[x][y] == State::EMPTY)
						{
							//��̃p�l�����������炷�ׂĖ��܂��Ă���t���O��false�ɂ���
							isAllFill_ = false;
							break;
						}
					}
				}
			}
		}

		//�����ڂ̃p�l���̔z����X�V
		DisplayPanelUpdate(nowMino_);

		sprite_->Update(systemPanel_, displayPanel_);
	}
	else
	{
		sprite_->Update(systemPanel_, displayPanel_);
	}
}

void Panel::DrawSprite()
{
	sprite_->Draw();
}

void Panel::DrawImGui()
{
	ImGui::Begin("Panel");
	//�z��\��
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

	//�I�����Ă���p�l���ꏊ�ύX
	ImGui::InputInt("x", (int*)&selectPos_.x);
	ImGui::InputInt("y", (int*)&selectPos_.y);
	//�I�����Ă���~�m�ύX
	std::string typeName;
	static int panelType = 0;
	ImGui::InputInt("type", &panelType);
	panelType = Clamp(panelType, 0, 6);
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

	//�I�����Ă���~�m��ݒu
	if (ImGui::Button("SetPanel")) {
		SetPanel(MinoList::GetMinoList((MinoType)panelType));
	}
	//���Z�b�g
	if (ImGui::Button("Reset")) {
		PanelReset();
	}
	//���̃��E���h�ɍs�����߂̏���������
	if (ImGui::Button("NextRound")) {
		PanelUpdate();
	}

	ImGui::Text("isAllFill : %d", isAllFill_);
	ImGui::Text("emptyPanelNum : %d", emptyPanelNum_);
	ImGui::Text("totalPanel_ : %d", totalPanel_);

	ImGui::End();
}

void Panel::PanelUpdate()
{
	attackPanelNum_ = 0;
	for (uint32_t y = 0; y < displayPanel_.size(); y++)
	{
		for (uint32_t x = 0; x < displayPanel_[y].size(); x++)
		{
			if (x == 0 || x == 9 || y == 0 || y == 9) {
				if (systemPanel_[x][y] == State::NEXT_RELEASE) {
					isPanelReset_ = true;
					if (x == 0)stateUp_.healthUp_++;
					if (x == 9)stateUp_.attackUp_++;
					if (y == 0)stateUp_.luckUp_++;
					if (y == 9)stateUp_.recoverUp_++;
				}
			}
			//NEXT_RELEASE���U���\�p�l���ɂ��čU���p�l�������Z�b�g����
			if (systemPanel_[x][y] == State::NEXT_RELEASE) {
				systemPanel_[x][y] = State::EMPTY;
			}
			else if (systemPanel_[x][y] == State::ATTACK) {
				systemPanel_[x][y] = State::EMPTY;
				//�U���p�l�����J�E���g����
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

	isPanelReset_ = false;
}

void Panel::ReDoReset()
{
	oldPanelList_.clear();
	usedMinoType_.clear();
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
			//��̃p�l���Əd�Ȃ��Ă�����
			if (systemPanel_[x][y] == State::EMPTY &&
				mino.panel_[panelY][panelX] == 1)
			{
				result = true;
			}
			//NEXT_RELEASE�Əd�Ȃ��Ă����瑦false��Ԃ�
			else if (systemPanel_[x][y] == State::NEXT_RELEASE &&
				mino.panel_[panelY][panelX] == 1)
			{
				return false;
			}
			//ATTACK�Əd�Ȃ��Ă����瑦false��Ԃ�
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
				systemPanel_[x][y] == State::EMPTY || systemPanel_[x][y] == State::NOT_OPEN ||
				systemPanel_[x][y] == State::PowerUp || systemPanel_[x][y] == State::Recovery;
			//��̃p�l���ɔz�u������
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
	//�E�[�A���[�̍��W
	uint32_t sizeY = selectPos_.y + (uint32_t)mino.panel_.size() - 1;
	uint32_t sizeX = selectPos_.x + (uint32_t)mino.panel_[0].size() - 1;

	uint32_t panelsizeY = (uint32_t)systemPanel_.size() - 1;
	uint32_t panelsizeX = (uint32_t)systemPanel_[0].size() - 1;
	//��r�����l���ړ�������
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

Mino Panel::SetRotMino(const Mino& mino)
{
	Mino result{};

	size_t sizeX = mino.panel_[0].size();
	size_t sizeY = mino.panel_.size();
	if (rotNum_ == 0) {
		result = mino;
		return result;
	}
	if (rotNum_ == 1) {
		result.panel_.resize(sizeX);//x
		for (int32_t i = 0; i < result.panel_.size(); i++)
		{
			result.panel_[i].resize(sizeY);//y
		}
	}
	else if (rotNum_ == 2) {
		result.panel_.resize(sizeY);//x
		for (int32_t i = 0; i < result.panel_.size(); i++)
		{
			result.panel_[i].resize(sizeX);//y
		}
	}
	else if (rotNum_ == 3) {
		result.panel_.resize(sizeX);//x
		for (int32_t i = 0; i < result.panel_.size(); i++)
		{
			result.panel_[i].resize(sizeY);//y
		}
	}

	for (uint32_t y = 0; y < sizeY; y++) {
		for (uint32_t x = 0; x < sizeX; x++) {
			if (rotNum_ == 1) {
				result.panel_[x][y] =
					mino.panel_[sizeY - 1 - y][x];
			}
			else if (rotNum_ == 2) {
				result.panel_[y][x] =
					mino.panel_[sizeY - 1 - y][sizeX - 1 - x];
			}
			else if (rotNum_ == 3) {
				result.panel_[x][y] =
					mino.panel_[y][sizeX - 1 - x];
			}
		}
	}
	return result;
}

void Panel::ReDo(std::vector<MinoType>* minos)
{
	if (oldPanelList_.size() > 0 && usedMinoType_.size() > 0) {
		int32_t sizeY = (int32_t)oldPanelList_.front().size();
		int32_t sizeX = (int32_t)oldPanelList_.front()[0].size();
		for (int32_t y = 0; y < sizeY; y++)
		{
			for (int32_t x = 0; x < sizeX; x++)
			{
				systemPanel_[y][x] = oldPanelList_.front()[y][x];
			}
		}
		oldPanelList_.erase(oldPanelList_.begin());

		minos->insert(minos->begin(), usedMinoType_.front());

		usedMinoType_.erase(usedMinoType_.begin());
	}
}

void Panel::SetPanel(const Mino& mino)
{
	if (IsCanChange(mino) == false) {
		SoundManager::Play("CantSetSE", false, 1.0f);
		return;
	}

	SoundManager::Play("SetSE", false, 1.0f);

	oldPanelList_.push_front(systemPanel_);
	usedMinoType_.push_front(minoType_);

	uint32_t sizeY = selectPos_.y + (uint32_t)mino.panel_.size();
	uint32_t sizeX = selectPos_.x + (uint32_t)mino.panel_[0].size();

	uint32_t panelX = 0;
	uint32_t panelY = 0;

	uint32_t nextReleaseNum = 0;

	for (uint32_t y = selectPos_.y; y < sizeY; y++)
	{
		panelX = 0;
		for (uint32_t x = selectPos_.x; x < sizeX; x++)
		{
			//��̃p�l���ɔz�u������
			if (systemPanel_[x][y] == State::EMPTY &&
				mino.panel_[panelY][panelX] == 1)
			{
				systemPanel_[x][y] = State::ATTACK;
			}
			//�J���Ă��Ȃ��p�l���ɔz�u������
			else if (systemPanel_[x][y] == State::NOT_OPEN &&
				mino.panel_[panelY][panelX] == 1)
			{
				systemPanel_[x][y] = State::NEXT_RELEASE;
				nextReleaseNum++;
			}
			else if (systemPanel_[x][y] == State::PowerUp &&
				mino.panel_[panelY][panelX] == 1)
			{
				systemPanel_[x][y] = State::NEXT_RELEASE;
				powerUpPanelNum_++;
			}
			else if (systemPanel_[x][y] == State::Recovery &&
				mino.panel_[panelY][panelX] == 1)
			{
				systemPanel_[x][y] = State::NEXT_RELEASE;
				recoveryPanelNum_++;
			}
			//�S�čX�V����
			displayPanel_[x][y] = systemPanel_[x][y];

			panelX++;
		}
		panelY++;
	}
	isSetComplete_ = true;

	totalPanel_ += nextReleaseNum;
}
uint32_t Panel::GetPowerUpPanelNum()
{
	uint32_t result = powerUpPanelNum_;
	powerUpPanelNum_ = 0;
	return result;
}
uint32_t Panel::GetRecoveryPanelNum()
{
	uint32_t result = recoveryPanelNum_;
	recoveryPanelNum_ = 0;
	return result;
}
void Panel::ResetStateUp()
{
	stateUp_.attackUp_ = 0;
	stateUp_.healthUp_ = 0;
	stateUp_.luckUp_ = 0;
	stateUp_.recoverUp_ = 0;
}
#pragma endregion

#pragma region PanelSprite
PanelSprite::PanelSprite(uint32_t panelSize, Vector2 basePos, float panelScale)
{
	//�z�񏉊���
	panels_.resize(panelSize);
	for (uint32_t i = 0; i < panelSize; i++)
	{
		panels_[i].resize(panelSize);
	}

	for (uint32_t y = 0; y < panels_.size(); y++)
	{
		for (uint32_t x = 0; x < panels_[y].size(); x++)
		{
			YGame::YTransform::Status status;

			status.pos_ = {
				basePos.x + (32.f * panelScale) * x,
				basePos.y + (32.f * panelScale) * y,
				0.0f
			};

			status.scale_ = { panelScale, panelScale, 0.0f };

			panels_[x][y].Initialize(status, nullptr);
		}
	}
}

void PanelSprite::Update(const std::vector<std::vector<int32_t>>& system, const std::vector<std::vector<int32_t>>& display)
{
	for (uint32_t y = 0; y < panels_.size(); y++)
	{
		for (uint32_t x = 0; x < panels_[y].size(); x++)
		{
			if (display[x][y] != State::PowerUp &&
				display[x][y] != State::Recovery &&
				display[x][y] != State::TEMPPOS) {
				panels_[x][y].SetTexture(TextureManager::GetInstance()->GetTexture("Panel"));
			}

			//�p�l���̐F�ύX
			if (display[x][y] == State::NOT_OPEN) {
				panels_[x][y].ChangeColor(YGame::BlockColorType::Gray);
				panels_[x][y].ResetAnime();
			}
			else if (display[x][y] == State::EMPTY) {
				panels_[x][y].ChangeColor(YGame::BlockColorType::White);
				panels_[x][y].ResetAnime();
			}
			else if (display[x][y] == State::ATTACK) {
				panels_[x][y].ChangeColor(YGame::BlockColorType::Orange);
				SetAnimation(x, y);
			}
			else if (display[x][y] == State::SELECT) {
				panels_[x][y].ChangeColor(YGame::BlockColorType::Orange);
			}
			else if (display[x][y] == State::NEXT_RELEASE) {
				panels_[x][y].ChangeColor(YGame::BlockColorType::Blue);
				OpenAnimation(x, y);
			}
			else if (display[x][y] == State::TEMPPOS) {
				panels_[x][y].ChangeColor(YGame::BlockColorType::Cyan);
			}
			else if (display[x][y] == State::PowerUp) {
				panels_[x][y].SetTexture(TextureManager::GetInstance()->GetTexture("PowerUpPanel"));
				panels_[x][y].ChangeColor(YGame::BlockColorType::White);
			}
			else if (display[x][y] == State::Recovery) {
				panels_[x][y].SetTexture(TextureManager::GetInstance()->GetTexture("RecoveryPanel"));
				panels_[x][y].ChangeColor(YGame::BlockColorType::White);
			}

			if (system[x][y] == State::NOT_OPEN) {
				panels_[x][y].ValidAnimtion();
			}
			else if (system[x][y] == State::EMPTY) {
				panels_[x][y].InvalidAnimtion();
			}

			panels_[x][y].Update();
		}
	}
}

void PanelSprite::SetAnimation(const size_t x, const size_t y)
{
	panels_[x][y].SetAnimation();
}

void PanelSprite::OpenAnimation(const size_t x, const size_t y)
{
	panels_[x][y].OpenAnimation();
}

void PanelSprite::Draw()
{
	for (uint32_t y = 0; y < panels_.size(); y++)
	{
		for (uint32_t x = 0; x < panels_[y].size(); x++)
		{
			panels_[x][y].Draw();
		}
	}
}

#pragma endregion