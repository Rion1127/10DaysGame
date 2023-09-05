#include "EnemyManager.h"
#include "Enemy.h"
#pragma region
EnemyManager::EnemyManager()
{
#ifdef _DEBUG
	list_.SetEnemy("Stage1", &enemyList_);

	nowEnemy_.swap(enemyList_[0]);
	enemyList_.erase(enemyList_.begin());
#endif // _DEBUG

	isChangeNowEnemy_ = false;
}
void EnemyManager::Update()
{
	if (nowEnemy_ == nullptr) {
		if (enemyList_.size() > 0) {
			nowEnemy_.swap(enemyList_[0]);
			enemyList_.erase(enemyList_.begin());
			isChangeNowEnemy_ = true;
		}
		//“G‚ÌŽc‚è‚ª‚¢‚È‚¢Žž
		else {
			isAllEnemyDestroy_ = true;
		}
	}

	if (nowEnemy_ != nullptr) {
		nowEnemy_->Update();

		if (nowEnemy_->GetIsAlive() == false) {
			nowEnemy_.release();
		}
	}
}
void EnemyManager::Draw()
{
	if (nowEnemy_ != nullptr) {
		nowEnemy_->Draw();
	}
}
void EnemyManager::DrawImGui()
{
}
#pragma endregion

#pragma region
EnemyPopDataList::EnemyPopDataList()
{
	PopData stage1;
	stage1.enemyData.resize(2);
	for (int32_t i = 0; i < stage1.enemyData.size(); i++) {
		stage1.enemyData[i] = {
			10,
			5 + (2 * i)
		};
	}
	dataList_.insert(std::make_pair("Stage1",stage1));
}

void EnemyPopDataList::SetEnemy(std::string name, std::vector<std::unique_ptr<IEnemy>>* enemy)
{
	enemy->clear();
	const auto& eData = dataList_.find(name)->second.enemyData;
	for (uint32_t i = 0; i < eData.size(); i++) {
		std::unique_ptr<IEnemy> newEnemy =
			std::make_unique<Enemy>(eData[i].health, eData[i].attackPower);

		enemy->emplace_back(std::move(newEnemy));
	}
}


#pragma endregion

