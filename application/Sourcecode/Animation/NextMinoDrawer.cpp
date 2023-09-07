#include "NextMinoDrawer.h"

using YGame::NextMinoDrawer;

void NextMinoDrawer::Initialize()
{
	for (size_t i = 0; i < nextMinos_.size(); i++)
	{
		YTransform::Status status;

		if (i == 0)
		{
			status.pos_ = 
			{ 
				570.0f, 
				300.0f, 
				0.0f 
			};
			status.scale_ = { 2.0f,2.0f,0.0f };
		}
		else
		{
			status.pos_ = 
			{ 
				580.0f,
				300.0f + 100.0f * static_cast<float>(i), 
				0.0f };
			status.scale_ = { 1.0f,1.0f,0.0f };
		}

		nextMinos_[i].Initialize(status);
	}
}

void NextMinoDrawer::Update(const std::vector<MinoType>& minos)
{
	// 前回と変わっていたらパーツを変更する
	ChangeNextMino(minos);

	for (size_t i = 0; i < nextMinos_.size(); i++)
	{
		nextMinos_[i].Update();
	}

	elderMinos_ = minos;
}

void NextMinoDrawer::Draw()
{
	for (size_t i = 0; i < nextMinos_.size(); i++)
	{
		nextMinos_[i].Draw();
	}
}

void NextMinoDrawer::ChangeNextMino(const std::vector<MinoType>& minos)
{
	if (minos.size() <= 0) { return; }

	size_t index = 0;
	while (true)
	{
		bool isEndCurrent = minos.size() <= index;
		bool isEndElder = elderMinos_.size() <= index;

		// パーツ増加時
		if (isEndCurrent == false && isEndElder)
		{
			nextMinos_[index].ChangeMinoAnimation(minos[index]);
		}
		
		// パーツ減少時
		if (isEndCurrent && isEndElder == false)
		{
			nextMinos_[index].InvisibleMinoAnimation();
		}

		// パーツ変更時
		if (isEndCurrent == false && isEndElder == false)
		{
			if (elderMinos_[index] != minos[index])
			{
				nextMinos_[index].ChangeMinoAnimation(minos[index]);
			}
		}

		if (nextMinos_.size() <= ++index) { return; }
	}
}

void NextMinoDrawer::NextMino::Initialize(const YTransform::Status& trfmStatus)
{
	trfm_.Initialize(trfmStatus);
	drawer_.Initialize(YTransform::Status::Default(), &trfm_.m_, BlockColorType::None);

	slime_.Initialize(
		20,
		{
			Vector3( 0.0f, 0.0f, 0.0f),
			-trfmStatus.scale_ ,
			Vector3( 0.0f, 0.0f, 0.0f),
		}, 
		3.0f);

	colorTim_.Initialize(5);
}

void NextMinoDrawer::NextMino::Update()
{
	// 見えなくなった瞬間に色を変える
	colorTim_.Update();
	if (colorTim_.IsEnd())
	{
		BlockColorType colorType = BlockColorType::None;

		if (isInvisible_ == false)
		{
			if (type_ == MinoType::Omino) { colorType = BlockColorType::Yellow; }
			if (type_ == MinoType::Tmino) { colorType = BlockColorType::Purple; }
			if (type_ == MinoType::Smino) { colorType = BlockColorType::Green; }
			if (type_ == MinoType::Zmino) { colorType = BlockColorType::Red; }
			if (type_ == MinoType::Imino) { colorType = BlockColorType::Cyan; }
			if (type_ == MinoType::Lmino) { colorType = BlockColorType::Orange; }
			if (type_ == MinoType::Jmino) { colorType = BlockColorType::Blue; }
		}

		drawer_.ChangeColor(colorType);

		colorTim_.Reset();
	}

	slime_.Update();

	Vector3 scale;

	if (slime_.IsAct())
	{
		scale = slime_.WobbleScaleValue(SlimeActor::EaseType::eOut);
	}

	trfm_.UpdateMatrix({ {}, {}, scale });
	drawer_.Update();
}

void NextMinoDrawer::NextMino::Draw()
{
	drawer_.Draw();
}

void NextMinoDrawer::NextMino::ChangeMinoAnimation(const MinoType type)
{
	type_ = type;

	slime_.Wobble();
	colorTim_.Reset(true);
	
	isInvisible_ = false;
}

void NextMinoDrawer::NextMino::InvisibleMinoAnimation()
{
	slime_.Wobble();
	colorTim_.Reset(true);
	
	isInvisible_ = true;
}

