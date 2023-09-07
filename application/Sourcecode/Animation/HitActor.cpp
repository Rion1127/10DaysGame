#include "HitActor.h"
#include <cassert>

using YGame::HitActor;

const Color kDefColor = Color(255, 255, 255, 255);
const Color kHitColor = Color(255, 0, 0, 255);

void HitActor::Initialize()
{
	isAct_ = false;

	shake_.Initialize();

	colorValue_ = kDefColor;
}

void HitActor::Update()
{
	if (isAct_ == false) { return; }

	shake_.Update();

	colorValue_ = kHitColor;

	if (shake_.IsAct() == false)
	{
		isAct_ = false;

		colorValue_ = kDefColor;
	}
}

void HitActor::Hit(const float swing, const float dekey)
{
	isAct_ = true;

	shake_.Initialize();
	shake_.Activate(swing, dekey);
}

