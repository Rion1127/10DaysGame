#include "RecoveryDrawer.h"
#include "mSound.h"

using YGame::RecoveryDrawer;

void RecoveryDrawer::CreateDigits()
{
	for (size_t i = 0; i < digits_.size(); i++)
	{
		digits_[i] = std::make_unique<RecoveryDigitDrawer>();
	}
}

void RecoveryDrawer::Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent, const int32_t number)
{
	NumberDrawer::Initialize(trfmStatus, matParent, number);

	dispTim_.Initialize(50);

	for (size_t i = 0; i < plusDras_.size(); i++)
	{
		YTransform::Status status = trfmStatus;

		if (i == 0) { status.pos_ += Vector3(-32.0f, +32.0f + 64.0f, 0.0f); }
		if (i == 1) { status.pos_ += Vector3(-16.0f,   0.0f + 64.0f, 0.0f); }
		if (i == 2) { status.pos_ += Vector3(+32.0f, +16.0f + 64.0f, 0.0f); }

		plusDras_[i].Initialize(status, matParent);
	}
}

void RecoveryDrawer::Update(const YTransform::Status& animeStatus)
{
	dispTim_.Update();
	if (dispTim_.IsEnd())
	{
		for (size_t i = 0; i < digits_.size(); i++)
		{
			static_cast<RecoveryDigitDrawer*>(digits_[i].get())->SetIsDisp(false);
		}

		for (size_t i = 0; i < plusDras_.size(); i++)
		{
			plusDras_[i].SetIsDisp(false);
		}
	}

	NumberDrawer::Update(animeStatus);

	for (size_t i = 0; i < plusDras_.size(); i++)
	{
		plusDras_[i].Update();
	}
}

void RecoveryDrawer::Draw()
{
	for (size_t i = 0; i < plusDras_.size(); i++)
	{
		plusDras_[i].Draw();
	}
	
	NumberDrawer::Draw();
}

void RecoveryDrawer::RecoverAnimation()
{
	dispTim_.Reset(true);
	for (size_t i = 0; i < digits_.size(); i++)
	{
		digits_[i]->ResetAnimation();
		static_cast<RecoveryDigitDrawer*>(digits_[i].get())->RiseAnimation();
	}
	for (size_t i = 0; i < plusDras_.size(); i++)
	{
		plusDras_[i].ResetAnimation();
		plusDras_[i].EmitAnimation();
	}
	SoundManager::Play("RecoverySE");
}


void RecoveryDrawer::RecoveryDigitDrawer::Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent, const int8_t digit)
{
	DigitDrawer::Initialize(trfmStatus, matParent, digit);

	riseTim_.Initialize(40);
	riseHeight_.Initialize(0.0f, -32.0f, 4.0f);
	riseScale_.Initialize(-1.0f, 0.0f, 4.0f);

	alphaPow_.Initialize(8);
	alphaEas_.Initialize(0.0f, 1.0f, 3.0f);
}

void RecoveryDrawer::RecoveryDigitDrawer::RiseAnimation()
{
	isDisp_ = true;

	riseTim_.Reset(true);
	alphaPow_.Reset();
}

void RecoveryDrawer::RecoveryDigitDrawer::ResetAnimation()
{
	isDisp_ = false;

	riseTim_.Reset();
	alphaPow_.Reset();
}

void RecoveryDrawer::RecoveryDigitDrawer::UpdateAnimation()
{
	riseTim_.Update();

	animeStatus_.pos_.y += riseHeight_.Out(riseTim_.Ratio());

	float scale = riseScale_.Out(riseTim_.Ratio());
	animeStatus_.scale_ += Vector3(scale / 10.0f, scale, 0.0f);

	alphaPow_.Update(isDisp_);

	float alphaRatio = alphaEas_.InOut(alphaPow_.Ratio());
	sprite_.SetColor(Color(20, 200, 20, 255 * alphaRatio));
}


void RecoveryDrawer::PlusDrawer::Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent)
{
	BaseInitialize(trfmStatus, matParent);
	sprite_.SetTexture(TextureManager::GetInstance()->GetTexture("Recovery"));

	emitTim_.Initialize(40);
	heightEas_.Initialize(0.0f, -16.0f, 4.0f);

	alphaPow_.Initialize(4);
	alphaEas_.Initialize(0.0f, 1.0f, 3.0f);
}

void RecoveryDrawer::PlusDrawer::EmitAnimation()
{
	isDisp_ = true;

	emitTim_.Reset(true);
	alphaPow_.Reset();
}

void RecoveryDrawer::PlusDrawer::ResetAnimation()
{
	isDisp_ = false;

	emitTim_.Reset();
	alphaPow_.Reset();
}

void RecoveryDrawer::PlusDrawer::UpdateAnimation()
{
	emitTim_.Update();
	animeStatus_.pos_.y += heightEas_.Out(emitTim_.Ratio());

	alphaPow_.Update(isDisp_);
	float alphaRatio = alphaEas_.Out(alphaPow_.Ratio());
	sprite_.SetColor(Color(255, 255, 255, 255 * alphaRatio));
}