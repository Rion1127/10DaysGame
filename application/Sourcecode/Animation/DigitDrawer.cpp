#include "DigitDrawer.h"

using YGame::DigitDrawer;

static const Vector2 kNumberSize = { 128.0f,128.0f };

void DigitDrawer::Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent, const int8_t digit)
{
	BaseInitialize(trfmStatus, matParent);
	sprite_.SetTexture(TextureManager::GetInstance()->GetTexture("Number"));

	SetDigit(digit);
}

void DigitDrawer::SetDigit(const int8_t digit)
{
	digit_ = (std::min)(digit, static_cast<int8_t>(9));

	sprite_.SetTex_LeftTop({ kNumberSize.x * static_cast<float>(digit_), 0.0f });
	sprite_.SetTex_Size({ kNumberSize.x, kNumberSize.y });

	trfm_.scale_ = Vector3(1.0f / 10.0f, 1.0f, 0.0f);
}