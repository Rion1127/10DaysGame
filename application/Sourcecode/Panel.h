#pragma once
#include <vector>
#include <array>
#include "Mino.h"
#include "Vector2.h"
#include "mInput.h"
#include "Sprite.h"

#include "YTransform.h"
#include "SlimeActor.h"
#include "Ease.h"

enum State {
	NOT_OPEN,
	EMPTY,
	ATTACK,
	NEXT_RELEASE,
	SELECT,
	TEMPPOS
};
enum class UpdateType {
	All,
	SpriteOnly
};

class PanelSprite {
private:
	struct PanelStatus
	{
		YGame::YTransform trfm_;
		YGame::SlimeActor slimeActor_;
		YMath::YTimer rotaTim_;
		Sprite sprite_;

		bool isSet_ = false;
		bool isOpen_ = false;
	};
private:
	std::vector<std::vector<PanelStatus>> panels_;
	YMath::Ease<float> rotaEas_;
public:
	PanelSprite(uint32_t panelSize,Vector2 basePos, float panelScale);

	void Update(const std::vector<std::vector<int32_t>>& panel);
	void Draw();
private:
	void SetAnimation(const size_t x, const size_t y);
	void OpenAnimation(const size_t x, const size_t y);
};

class Panel
{
private:
	
	struct SelectPos {
		int32_t x;
		int32_t y;
	};
private:
	//�`��p�̃p�l��
	std::vector<std::vector<int32_t>> displayPanel_;
	//�V�X�e����̃p�l��
	std::vector<std::vector<int32_t>> systemPanel_;
	int32_t maxPanelSize_;
	int32_t initalSize_;
	//���ݑI�����Ă���p�l����̍��W
	SelectPos selectPos_;

	Vector2 spritePos_;
	float spriteSize_;
	float spriteScale_;
	std::unique_ptr<PanelSprite> sprite_;

	MinoType minoType_;
	bool isSetComplete_;
	bool isAllFill_;
	UpdateType updateType_;
	int32_t attackPanelNum_;
	int32_t emptyPanelNum_;
	//��]��������
	//0,0�x�@1,90�x 2,180�x 3,270�x
	uint32_t rotNum_;
	Mino nowMino_;
public:
	Panel();
	void Update();
	void DrawSprite();

	void DrawImGui();
public:
	//�p�l�������̃^�[���ɂ���
	void PanelUpdate();
	void PanelReset();
private:
	//�p�l�����Z�b�g�ł��邩�m�F����
	bool IsCanChange(const Mino& mino);
	void DisplayPanelUpdate(const Mino& mino);
	void SelectPosClamp(const Mino& mino);
	Mino SetRotMino(const Mino& mino);
public:
	//�p�l�����Z�b�g����
	void SetPanel(const Mino& mino);
	void SetSelectPos(Vector2 pos) { selectPos_.x = (int32_t)pos.x; selectPos_.y = (int32_t)pos.y;}
	void SetisSetComplete(bool flag) { isSetComplete_ = flag; }
	void SetMinoType(MinoType type) { minoType_ = type; }
	void SetUpdateType(UpdateType type) { updateType_ = type; }
	void SetRotNum(uint32_t rotnum) { rotNum_ = rotnum; }
public:
	bool GetisSetComplete() { return isSetComplete_; }
	bool GetIsAllFill() { return isAllFill_; }
	int32_t GetAttackPanelNum() { return attackPanelNum_; }
	int32_t GetEmptyPanelNum() { return emptyPanelNum_; }
	Mino GetNowMino() { return nowMino_; }

	std::vector<std::vector<int32_t>> GetDisplayPanel() { return displayPanel_; }
};