#include "Shake.h"
#include "RRandom.h"

using YMath::Shake;

void Shake::Initialize()
{
	// 初期化
	isAct_ = false;
	swing_ = 0.0f;
	dekey_ = 0.0f;
	value_ = {};
}

void Shake::Activate(const float swing, const float dekey)
{
	// 動作していないなら
	if (!isAct_)
	{
		// 初期化 + 代入
		dekey_ = dekey;
		swing_ = swing;
		value_ = {};

		// 動作開始
		isAct_ = true;
	}
	// 揺れ量が今より大きいなら
	else if (swing_ <= swing)
	{
		// 代入
		dekey_ = dekey;
		swing_ = swing;
	}
}

void Shake::Update()
{
	// 範囲が0以上なら
	if (swing_ > 0) 
	{
		// 範囲を狭める
		swing_ -= dekey_; 
	}
	
	// 範囲が0以下なら
	if (swing_ <= 0)
	{
		// 初期化
		Initialize();
	}
	
	// 動作中なら
	if (isAct_)
	{
		// 範囲内の乱数生成
		value_.x = RRandom::RandF(-swing_, swing_);
		value_.y = RRandom::RandF(-swing_, swing_);
		//value_.z = RRandom::RandF(-swing_, swing_);
	}
}
