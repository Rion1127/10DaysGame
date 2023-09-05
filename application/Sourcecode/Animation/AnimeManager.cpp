#include "AnimeManager.h"

AnimeManager* AnimeManager::GetInstance()
{
	static AnimeManager instance;
	return &instance;
}
