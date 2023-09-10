#include "EnemyManager.h"
#include "Enemy.h"
#pragma region
EnemyManager::EnemyManager()
{
#ifdef _DEBUG
#endif // _DEBUG
	list_.SetEnemy("MainGame", &enemyList_);

	nowEnemy_.swap(enemyList_[0]);
	enemyList_.erase(enemyList_.begin());

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
			nowEnemy_.reset();
			nowEnemy_ = nullptr;
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
	PopData mainGame;
	mainGame.enemyData.resize(3);
	for (int32_t i = 0; i < mainGame.enemyData.size(); i++) {
		mainGame.enemyData[i] = {
			10000 + 4 * i,
			3 + (2 * i)
		};
	}
	dataList_.insert(std::make_pair("MainGame", mainGame));
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

