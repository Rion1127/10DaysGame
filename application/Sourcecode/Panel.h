#pragma once
#include <vector>
#include <array>
#include <list>
#include "Mino.h"
#include "Vector2.h"
#include "mInput.h"
#include "Sprite.h"
#include "Collision.h"

#include "PanelDrawer.h"

enum State {
	NOT_OPEN,
	EMPTY,
	ATTACK,
	NEXT_RELEASE,
	SELECT,
	TEMPPOS,
	TEMPPOS_ON_EMPTY,
	CANTSET
};
enum class UpdateType {
	All,
	SpriteOnly
};

class PanelSprite {
private:
	std::vector<std::vector<YGame::PanelDrawer>> panels_;
public:
	PanelSprite(uint32_t panelSize,Vector2 basePos, float panelScale);
	void Update(
		const std::vector<std::vector<int32_t>>& system, 
		const std::vector<std::vector<int32_t>>& display1,
		const std::vector<std::vector<int32_t>>& display2);
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

	struct StateUp {
		int32_t luckUp_;
		int32_t guardUp_;
		int32_t recoverUp_;
		int32_t attackUp_;
	};
private:
	//描画用のパネル
	std::vector<std::vector<int32_t>> displayPanel1_;
	std::vector<std::vector<int32_t>> displayPanel2_;
	//システム上のパネル
	std::vector<std::vector<int32_t>> systemPanel_;
	std::list<std::vector<std::vector<int32_t>>> oldPanelList_;
	std::list<MinoType> usedMinoType_;
	std::list<uint32_t> oldTotalPanel_;
	std::list<StateUp> oldStateUp_;
	int32_t maxPanelSize_;
	int32_t initalSize_;
	//現在選択しているパネル上の座標
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
	//回転情報を示す
	//0,0度　1,90度 2,180度 3,270度
	uint32_t rotNum_;
	Mino nowMino_;
	Box2D allPanelSize_;

	uint32_t totalPanel_;
	
	bool isPanelReset_;

	StateUp stateUp_;
public:
	Panel();
	void Update();
	void DrawSprite();

	void DrawImGui();
public:
	//パネルを次のターンにする
	void PanelUpdate();
	void PanelReset();
	void ReDoReset();
	void ReDo(std::vector<MinoType>* minos);
private:
	//パネルをセットできるか確認する
	bool IsCanChange(const Mino& mino);
	void DisplayPanelUpdate(const Mino& mino);
	void SelectPosClamp(const Mino& mino);
	Mino SetRotMino(const Mino& mino);
public:
	//パネルをセットする
	void SetPanel(const Mino& mino);
	void SetSelectPos(Vector2 pos) { selectPos_.x = (int32_t)pos.x; selectPos_.y = (int32_t)pos.y;}
	void SetisSetComplete(bool flag) { isSetComplete_ = flag; }
	void ChangeMinoAnimation(MinoType type) { minoType_ = type; }
	void SetUpdateType(UpdateType type) { updateType_ = type; }
	void SetRotNum(uint32_t rotnum) { rotNum_ = rotnum; }
	void SetIsAllFill(bool flag) { isAllFill_ = flag; }
	void ResetStateUp();
public:
	bool GetisSetComplete() { return isSetComplete_; }
	bool GetIsAllFill() { return isAllFill_; }
	bool GetPanelReset() { return isPanelReset_; }
	int32_t GetAttackPanelNum() { return attackPanelNum_; }
	int32_t GetEmptyPanelNum() { return emptyPanelNum_; }
	Mino GetNowMino() { return nowMino_; }
	uint32_t GetPowerUpPanelNum();
	uint32_t GetRecoveryPanelNum();
	uint32_t GetTotalEmptyPanelNum() { return totalPanel_; };
	StateUp GetStateUpValue() { return stateUp_; }

	std::vector<std::vector<int32_t>> GetDisplayPanel() { return displayPanel1_; }
};