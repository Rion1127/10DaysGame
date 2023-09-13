#include "EnemyManager.h"
#include "Enemy.h"
#include "RRandom.h"
#include "SceneManager.h"
#include "Lerp.h"

#pragma region
EnemyManager::EnemyManager()
{
#ifdef _DEBUG
#endif // _DEBUG
	

	isChangeNowEnemy_ = false;
	
	helthRatio_ = 0.0f;
	attackRatio_ = 0.0f;
	guardRatio_ = 0.0f;
}
void EnemyManager::Update()
{
	if (nowEnemy_ == nullptr) {
		if (SceneManager::GetGameMode() == GameMode::MainGame)
		{
			if (enemyList_.size() > 0)
			{
				nowEnemy_.swap(enemyList_[0]);
				enemyList_.erase(enemyList_.begin());
				isChangeNowEnemy_ = true;
			}
			//“G‚ÌŽc‚è‚ª‚¢‚È‚¢Žž
			else
			{
				isAllEnemyDestroy_ = true;
			}
		}
		else if (SceneManager::GetGameMode() == GameMode::EndLess)
		{
			helthRatio_		+= 0.001f;
			attackRatio_	+= 0.01f;
			guardRatio_		+= 0.01f;


			int32_t enemyType = RRandom::Rand(0,2);

			int32_t health	 = static_cast<int32_t>(YMath::EaseIn(1.0f,  99999.0f, helthRatio_, 1.5f));
			int32_t power	 = static_cast<int32_t>(YMath::EaseIn(0.0f,    999.0f, attackRatio_, 1.5f));
			int32_t guard	 = static_cast<int32_t>(YMath::EaseIn(0.0f,    999.0f, guardRatio_, 1.5f));

			nowEnemy_ =
				std::make_unique<Enemy>(health, power, guard, YGame::EnemyType(enemyType));
			isChangeNowEnemy_ = true;
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
	// MAIN
	{
		PopData mainGame;
		mainGame.enemyData.resize(5);
		mainGame.enemyData[0] = {  25,  3,  0,YGame::EnemyType::Slime };
		mainGame.enemyData[1] = {  50,  5, 10,YGame::EnemyType::Slime };
		mainGame.enemyData[2] = {  50, 10, 50,YGame::EnemyType::Bat };
		mainGame.enemyData[3] = {  75, 20, 10,YGame::EnemyType::Bat };
		mainGame.enemyData[4] = { 150, 30, 50,YGame::EnemyType::Bear };
		dataList_.insert(std::make_pair("MainGame", mainGame));
	}

	// TUTOTIAL
	{
		PopData tutorial;
		tutorial.enemyData.resize(1);
		for (int32_t i = 0; i < tutorial.enemyData.size(); i++)
		{
			tutorial.enemyData[i] = {
				99999999,
				0,
				0,
				YGame::EnemyType::Slime
			};
		}
		dataList_.insert(std::make_pair("Tutorial", tutorial));
	}

	// ENDLESS
	{
		PopData endless;
		endless.enemyData.resize(1);
		for (int32_t i = 0; i < endless.enemyData.size(); i++)
		{
			endless.enemyData[i] = {
				1,
				0,
				0,
				static_cast<YGame::EnemyType>(RRandom::Rand(0, 2))
			};
		}
		dataList_.insert(std::make_pair("Endless", endless));
	}
}

void EnemyPopDataList::SetEnemy(std::string name, std::vector<std::unique_ptr<IEnemy>>* enemy)
{
	enemy->clear();
	const auto& eData = dataList_.find(name)->second.enemyData;
	for (uint32_t i = 0; i < eData.size(); i++) {
		std::unique_ptr<IEnemy> newEnemy =
			std::make_unique<Enemy>(eData[i].health, eData[i].attackPower, eData[i].guard, eData[i].type);

		enemy->emplace_back(std::move(newEnemy));
	}
}


#pragma endregion

