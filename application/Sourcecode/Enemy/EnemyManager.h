#pragma once
#include "IEnemy.h"
#include <vector>
#include <unordered_map>

struct EnemyData {
	int32_t health;
	int32_t attackPower;
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
	//�G
	std::vector<std::unique_ptr<IEnemy>> enemyList_;
	//���ݐ���Ă���G
	std::unique_ptr<IEnemy> nowEnemy_;
	bool isChangeNowEnemy_;
	bool isAllEnemyDestroy_;
public:
	EnemyManager();

	void Update();
	void Draw();
	void DrawImGui();

	IEnemy* GetNowEnemy() {
		return nowEnemy_.get();
	}
public:
	bool GetIsChangeNowEnemy() { return isChangeNowEnemy_; }
	bool GetIsAllEnemyDestroy() { return isAllEnemyDestroy_; }
public:
	void SetIsChangeNowEnemy(bool flag) { isChangeNowEnemy_ = flag; }
};

