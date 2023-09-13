#include "EnemyManager.h"
#include "Enemy.h"
#pragma region
EnemyManager::EnemyManager()
{
#ifdef _DEBUG
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

void EnemyManager::SetEnemyList(std::string name)
{
	enemyList_.clear();
	nowEnemy_ = nullptr;
	list_.SetEnemy(name, &enemyList_);

	nowEnemy_.swap(enemyList_[0]);
	enemyList_.erase(enemyList_.begin());
}
#pragma endregion

#pragma region
EnemyPopDataList::EnemyPopDataList()
{
	PopData mainGame;
	mainGame.enemyData.resize(3);
	for (int32_t i = 0; i < mainGame.enemyData.size(); i++) {
		mainGame.enemyData[i] = {
			100 + 4 * i,
			3 + (2 * i)
		};
	}
	dataList_.insert(std::make_pair("MainGame", mainGame));

	PopData tutorial;
	tutorial.enemyData.resize(1);
	for (int32_t i = 0; i < tutorial.enemyData.size(); i++)
	{
		tutorial.enemyData[i] = {
			99999999,
			0
		};
	}
	dataList_.insert(std::make_pair("Tutorial", tutorial));

	PopData endless;
	endless.enemyData.resize(999);
	for (int32_t i = 0; i < endless.enemyData.size(); i++)
	{
		endless.enemyData[i] = {
			100 + 4 * i,
			3 + (2 * i)
		};
	}
	dataList_.insert(std::make_pair("Endless", endless));
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

