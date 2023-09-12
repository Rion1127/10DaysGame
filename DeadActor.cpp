#include "DeadActor.h"
#include "Lerp.h"
#include "RRandom.h"

using YGame::DeadActor;

std::array<DeadActor::DebriDrawer, 100> DeadActor::sDebris_{};

namespace 
{
	const size_t kEmitNum = 20;
}

void DeadActor::Explosion(const Vector3& pos)
{
	size_t emitCounter = 0;
	for (size_t i = 0; i < sDebris_.size(); i++)
	{
		if (kEmitNum <= emitCounter) { return; }

		if (sDebris_[i].IsAlive()) { continue; }
		sDebris_[i].Emit(pos);
		
		emitCounter++;
	}
}

void DeadActor::StaticInitialize()
{
	for (size_t i = 0; i < sDebris_.size(); i++)
	{
		sDebris_[i].Initialize();
	}
}

void DeadActor::StaticUpdate()
{
	for (size_t i = 0; i < sDebris_.size(); i++)
	{
		sDebris_[i].Update();
	}
}

void DeadActor::StaticDraw()
{
	for (size_t i = 0; i < sDebris_.size(); i++)
	{
		sDebris_[i].Draw();
	}
}

void DeadActor::DebriDrawer::Initialize()
{
	BaseInitialize(YTransform::Status::Default(), nullptr);
	sprite_.SetTexture(TextureManager::GetInstance()->GetTexture("Debri"));

	aliveTim_.Initialize(40);
}

void DeadActor::DebriDrawer::Emit(const Vector3& pos)
{
	trfm_.pos_ = pos;

	aliveTim_.Reset(true);

	Vector3 posTop = { RRandom::RandF(-64.0f, +64.0f), RRandom::RandF(-64.0f, -16.0f),0.0f };
	Vector3 posEnd = { posTop.x * 1.5f, RRandom::RandF(64.0f, 96.0f), 0.0f };
	posEas_.Initialize({ {}, posTop, posEnd }, 1.5f);

	const float kRotaValue = 3.141592f * 2.0f;
	float rotaEnd = RRandom::RandF(-kRotaValue, kRotaValue);
	rotaEas_.Initialize(0.0f, rotaEnd, 3.0f);
	
	const float kScaleValue = 1.0f;
	float scaleStart = RRandom::RandF(0.0f, kScaleValue);
	scaleEas_.Initialize(0.0f, kScaleValue, 3.0f);

	color_ = Color(200, 200, 0, 255);
}

void DeadActor::DebriDrawer::UpdateAnimation()
{
	if (aliveTim_.IsAct() == false)
	{
		sprite_.SetColor(Color(0, 0, 0, 0));
		return;
	}

	aliveTim_.Update();
	if (aliveTim_.IsEnd())
	{
		aliveTim_.Reset(false);
	}

	animeStatus_.pos_ = posEas_.In(aliveTim_.Ratio());
	animeStatus_.rota_.z = rotaEas_.In(aliveTim_.Ratio());
	float scale = scaleEas_.In(aliveTim_.Ratio());
	animeStatus_.scale_ = Vector3(scale, scale, 0.0f);

	float alphaRatio = YMath::EaseIn(1.0f, 0.0f, aliveTim_.Ratio(), 2.0f);
	color_.a = 255 * alphaRatio;
	sprite_.SetColor(color_);
}
