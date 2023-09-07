#include "BlockDrawer.h"

using YGame::BlockColorType;
using YGame::BlockDrawer;

void BlockDrawer::Initialize(const YTransform::Status& trfmStatus, Matrix4* matParent, const BlockColorType& colorType)
{
	BaseInitialize(trfmStatus, matParent);
	sprite_.SetTexture(TextureManager::GetInstance()->GetTexture("Panel"));

	ChangeColor(colorType);
}

void BlockDrawer::ChangeColor(const BlockColorType colorType, const float alphaRatio)
{
	colorType_ = colorType;

	Color color;

	if (colorType_ == BlockColorType::None)		{ color = Color(  0,  0,  0,  0 * alphaRatio); }
	if (colorType_ == BlockColorType::White)	{ color = Color(200,200,200,255 * alphaRatio); }
	if (colorType_ == BlockColorType::Gray)		{ color = Color(100,100,100,255 * alphaRatio); }
	if (colorType_ == BlockColorType::Yellow)	{ color = Color(200,200,  0,255 * alphaRatio); }
	if (colorType_ == BlockColorType::Purple)	{ color = Color(200,  0,200,255 * alphaRatio); }
	if (colorType_ == BlockColorType::Green)	{ color = Color(  0,200,  0,255 * alphaRatio); }
	if (colorType_ == BlockColorType::Red)		{ color = Color(200,  0,  0,255 * alphaRatio); }
	if (colorType_ == BlockColorType::Cyan)		{ color = Color(  0,200,200,255 * alphaRatio); }
	if (colorType_ == BlockColorType::Orange)	{ color = Color(200,100,  0,255 * alphaRatio); }
	if (colorType_ == BlockColorType::Blue)		{ color = Color(  0,  0,200,255 * alphaRatio); }
	
	sprite_.SetColor(color);
}
