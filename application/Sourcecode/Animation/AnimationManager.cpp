#include "AnimationManager.h"

using YGame::AnimationManager;

AnimationManager* AnimationManager::GetInstance()
{
	static AnimationManager instance;
	return &instance;
}
