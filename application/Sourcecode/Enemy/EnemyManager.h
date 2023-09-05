#pragma once
#include "IEnemy.h"
#include <vector>
class EnemyManager
{
private:
	//“G
	std::vector<std::unique_ptr<IEnemy>> enemyList_;
	
private:
	EnemyManager();
};

