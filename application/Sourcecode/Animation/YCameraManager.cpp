#include "YCameraManager.h"
#include <algorithm>

void YCameraManager::Initialize()
{
    pos_ = {};
    shake_.Initialize();
}

void YCameraManager::Update()
{
    shake_.Update();
}

void YCameraManager::ShakeCamera(const float swing, const float dekey)
{
    static const float kSwingVal = 100.0f;
    float s = std::clamp(swing, -kSwingVal, kSwingVal);
    shake_.Activate(s, dekey);
}

Vector3 YCameraManager::GetCameraPos()
{
    return pos_ + shake_.Value();
}

YCameraManager* YCameraManager::GetInstance()
{
    static YCameraManager instance;
    return &instance;
}
