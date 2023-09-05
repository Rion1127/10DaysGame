#include "Shake.h"
#include "RRandom.h"

using YMath::Shake;

void Shake::Initialize()
{
	// ������
	isAct_ = false;
	swing_ = 0.0f;
	dekey_ = 0.0f;
	value_ = {};
}

void Shake::Activate(const float swing, const float dekey)
{
	// ���삵�Ă��Ȃ��Ȃ�
	if (!isAct_)
	{
		// ������ + ���
		dekey_ = dekey;
		swing_ = swing;
		value_ = {};

		// ����J�n
		isAct_ = true;
	}
	// �h��ʂ������傫���Ȃ�
	else if (swing_ <= swing)
	{
		// ���
		dekey_ = dekey;
		swing_ = swing;
	}
}

void Shake::Update()
{
	// �͈͂�0�ȏ�Ȃ�
	if (swing_ > 0) 
	{
		// �͈͂����߂�
		swing_ -= dekey_; 
	}
	
	// �͈͂�0�ȉ��Ȃ�
	if (swing_ <= 0)
	{
		// ������
		Initialize();
	}
	
	// ���쒆�Ȃ�
	if (isAct_)
	{
		// �͈͓��̗�������
		value_.x = RRandom::RandF(-swing_, swing_);
		value_.y = RRandom::RandF(-swing_, swing_);
		//value_.z = RRandom::RandF(-swing_, swing_);
	}
}
