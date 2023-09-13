#pragma once
#include "IEnemy.h"
#include <vector>
#include <unordered_map>

struct EnemyData {
	int32_t health;
	int32_t attackPower;
	int32_t guard;
	YGame::EnemyType type;
};

struct PopData {
	std::vector<EnemyData> enemyData;
};

class EnemyPopDataList {
private:
	std::unordered_map<std::string, PopData> dataList_;
public:
	EnemyPopDataList();

	void SetEnemy(std::string name,std::vector<std::unique_ptr<IEnemy>>* enemy);
};

class EnemyManager
{
private:
	EnemyPopDataList list_;
	//ìG
	std::vector<std::unique_ptr<IEnemy>> enemyList_;
	//åªç›êÌÇ¡ÇƒÇ¢ÇÈìG
	std::unique_ptr<IEnemy> nowEnemy_;
	bool isChangeNowEnemy_ = false;
	bool isAllEnemyDestroy_ = false;
public:
	EnemyManager();

	void Update();
	void Draw();
	void DrawImGui();

	void SetEnemyList(std::string name);

	IEnemy* GetNowEnemy() {
		return nowEnemy_.get();
	}
public:
	bool GetIsChangeNowEnemy() { return isChangeNowEnemy_; }
	bool GetIsAllEnemyDestroy() { return isAllEnemyDestroy_; }
	bool GetIsEnemyEmpty() { return nowEnemy_ == nullptr && enemyList_.size() <= 0; }
public:
	void SetIsChangeNowEnemy(bool flag) { isChangeNowEnemy_ = flag; }
};

