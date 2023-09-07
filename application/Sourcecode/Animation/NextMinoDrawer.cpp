#include "NextMinoDrawer.h"

using YGame::NextMinoDrawer;

void NextMinoDrawer::Initialize()
{
	static const float kScale = 0.75f;
	
		for (size_t i = 0; i < nextMinos_.size(); i++)
	{
		YTransform::Status status;

		if (i == 0)
		{
			status.scale_ = { 0.0f,0.0f,0.0f };
		}
		if (i == 1)
		{
			status.pos_ = 
			{ 
				600.0f, 
				300.0f, 
				0.0f 
			};
			status.scale_ = { kScale,kScale,0.0f };
		}
		else
		{

			status.pos_ = 
			{ 
				620.0f,
				250.0f + 75.0f * static_cast<float>(i), 
				0.0f };
			status.scale_ = { kScale / 1.5f,kScale / 1.5f,0.0f };
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
		if (i == 0) { continue; }
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

	for (size_t i = 0; i < drawers_.size(); i++)
	{
		drawers_[i].Initialize(YTransform::Status::Default(), &trfm_.m_, BlockColorType::None);
	}

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
		ChangeMino();

		colorTim_.Reset();
	}

	slime_.Update();

	Vector3 scale;

	if (slime_.IsAct())
	{
		scale = slime_.WobbleScaleValue(SlimeActor::EaseType::eOut);
	}

	trfm_.UpdateMatrix({ {}, {}, scale });

	for (size_t i = 0; i < drawers_.size(); i++)
	{
		drawers_[i].Update();
	}
}

void NextMinoDrawer::NextMino::Draw()
{
	for (size_t i = 0; i < drawers_.size(); i++)
	{
		drawers_[i].Draw();
	}
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

void NextMinoDrawer::NextMino::ChangeMino()
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

	for (size_t i = 0; i < drawers_.size(); i++)
	{
		drawers_[i].ChangeColor(colorType);
	}

	if (isInvisible_) { return; }

	// パネル位置変更
	std::vector<std::vector<uint32_t>> panel = MinoList::GetMinoList(type_).panel_;
	size_t dIndex = 0;

	Vector3 offset;

	if (type_ == MinoType::Omino) { offset = { -32.0f,-32.0f,0.0f }; }
	if (type_ == MinoType::Tmino) { offset = { -48.0f,-32.0f,0.0f }; }
	if (type_ == MinoType::Smino) { offset = { -48.0f,-32.0f,0.0f }; }
	if (type_ == MinoType::Zmino) { offset = { -48.0f,-32.0f,0.0f }; }
	if (type_ == MinoType::Imino) { offset = { -16.0f,-64.0f,0.0f }; }
	if (type_ == MinoType::Lmino) { offset = { -48.0f,-32.0f,0.0f }; }
	if (type_ == MinoType::Jmino) { offset = { -48.0f,-32.0f,0.0f }; }

	for (size_t i = 0; i < panel.size(); i++)
	{
		for (size_t j = 0; j < panel[i].size(); j++)
		{
			if (panel[i][j] != 1) { continue; }
		
			YTransform::Status status = YTransform::Status::Default();

			status.pos_ = { 32.0f * j, 32.0f * i, 0.0f };
			status.pos_ += offset;

			drawers_[dIndex].SetTransform(status);

			dIndex++;
		}
	}
}

