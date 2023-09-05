#pragma once
#include "IEnemy.h"
#include <vector>
#include <unordered_map>
class EnemyManager
{
private:
	//“G
	std::vector<std::unique_ptr<IEnemy>> enemyList_;
	
public:
	EnemyManager();
};

struct EnemyPopData{
	std::vector<IEnemy> enemyData;
};

class EnemyPopDataList {
private:
	std::unordered_map<std::string, EnemyPopData> dataList_;
public:
	EnemyPopDataList();
};