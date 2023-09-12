#include "StatusDrawer.h"

using YGame::StatusDrawer;

void StatusDrawer::Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent)
{
	trfm_.Initialize(trfmStatus);
	trfm_.parent_ = matParent;

	YTransform::Status counterStatus = YTransform::Status::Default();

	counter_.Initialize(counterStatus, &trfm_.m_, 0);

	plus_.Initialize();
	plus_.parent_ = &trfm_.m_;

	YTransform::Status signStatus = YTransform::Status::Default();
	
	sign_.Initialize(signStatus, &plus_.m_);
	sign_.SetColor(Color(200, 200, 20, 0));
	plusCounter_.Initialize(counterStatus, &plus_.m_, 0);
	plusCounter_.SetColor(Color(200, 200, 20, 0));

	moveTim_.Initialize(40);
	moveEas_.Initialize(-64.0f, 0.0f, 4.0f);
}

void StatusDrawer::Update()
{
	moveTim_.Update();
	if (moveTim_.IsEnd())
	{
		counter_.ChangeAnimation(number_);
		sign_.SetColor(Color(200, 200, 20, 0));
		plusCounter_.SetColor(Color(200, 200, 20, 0));
	}

	trfm_.UpdateMatrix();

	counter_.Update();

	plus_.UpdateMatrix({ { moveEas_.In(moveTim_.Ratio()), 0.0f,0.0f } });
	sign_.Update();
	plusCounter_.Update();
}

void StatusDrawer::PowerUpAnimation(const int32_t number)
{
	moveTim_.Reset(true);
	number_ = number;
}

void StatusDrawer::PlusAnimation(const int32_t plusNum)
{
	int32_t num = plusNum;
	float alpha = 255.0f;
	
	if (plusNum <= 0) 
	{
		num = 0;
		alpha = 0.0f; 
	}

	moveTim_.Reset(false);
	sign_.SetColor(Color(200, 200, 20, alpha));
	plusCounter_.ChangeAnimation(num);
	plusCounter_.SetColor(Color(200, 200, 20, alpha));
}

void StatusDrawer::Draw()
{
	counter_.Draw();
	plusCounter_.Draw();
}

void StatusDrawer::SignDrawer::Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent)
{
	BaseInitialize(trfmStatus, matParent);
	sprite_.SetTexture(TextureManager::GetInstance()->GetTexture("Recovery"));
}
