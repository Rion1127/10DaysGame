#include "Shake.h"
#include "RRandom.h"

using YMath::Shake;

void Shake::Initialize()
{
	// ‰Šú‰»
	isAct_ = false;
	swing_ = 0.0f;
	dekey_ = 0.0f;
	value_ = {};
}

void Shake::Activate(const float swing, const float dekey)
{
	// “®ì‚µ‚Ä‚¢‚È‚¢‚È‚ç
	if (!isAct_)
	{
		// ‰Šú‰» + ‘ã“ü
		dekey_ = dekey;
		swing_ = swing;
		value_ = {};

		// “®ìŠJn
		isAct_ = true;
	}
	// —h‚ê—Ê‚ª¡‚æ‚è‘å‚«‚¢‚È‚ç
	else if (swing_ <= swing)
	{
		// ‘ã“ü
		dekey_ = dekey;
		swing_ = swing;
	}
}

void Shake::Update()
{
	// ”ÍˆÍ‚ª0ˆÈã‚È‚ç
	if (swing_ > 0) 
	{
		// ”ÍˆÍ‚ğ‹·‚ß‚é
		swing_ -= dekey_; 
	}
	
	// ”ÍˆÍ‚ª0ˆÈ‰º‚È‚ç
	if (swing_ <= 0)
	{
		// ‰Šú‰»
		Initialize();
	}
	
	// “®ì’†‚È‚ç
	if (isAct_)
	{
		// ”ÍˆÍ“à‚Ì—”¶¬
		value_.x = RRandom::RandF(-swing_, swing_);
		value_.y = RRandom::RandF(-swing_, swing_);
		//value_.z = RRandom::RandF(-swing_, swing_);
	}
}
