#include "YTransform.h"

using YGame::YTransform;

Matrix4 MatIdentity()
{
	return Matrix4(
		1.0f, 0.0f, 0.0f ,0.0f,
		0.0f, 1.0f, 0.0f ,0.0f,
		0.0f, 0.0f, 1.0f ,0.0f,
		0.0f, 0.0f, 0.0f ,1.0f
	);
}

YTransform::YTransform() :
	pos_(0.0f, 0.0f, 0.0f),
	rota_(0.0f, 0.0f, 0.0f),
	scale_(1.0f, 1.0f, 1.0f),
	m_(MatIdentity()),
	parent_(nullptr)
{
	// �s��X�V
	UpdateMatrix();
}

YTransform::YTransform(const Status & status) :
	pos_(status.pos_),
	rota_(status.rota_),
	scale_(status.scale_),
	m_(MatIdentity()),
	parent_(nullptr)
{
	// �s��X�V
	UpdateMatrix();
}

YTransform::Status YTransform::Status::Default()
{
	// �߂�l�p
	Status result;
	
	// ������
	result.pos_ = Vector3(0.0f, 0.0f, 0.0f);
	result.rota_ = Vector3(0.0f, 0.0f, 0.0f);
	result.scale_ = Vector3(1.0f, 1.0f, 1.0f);

	// �Ԃ�
	return result;
}

void YTransform::Initialize(const Status& status)
{
	// ���
	pos_ = status.pos_;
	rota_ = status.rota_;
	scale_ = status.scale_;
	
	// �s��X�V
	UpdateMatrix();
}

void YTransform::UpdateMatrix()
{
	// �A�t�B���ϊ�
	Matrix4 matScale, matRota, matTrans;
	matScale = matRota = matTrans = MatIdentity();

	matScale = ConvertScalingMat(scale_);
	
	matRota *= ConvertRotationZAxisMat(rota_.z);
	matRota *= ConvertRotationXAxisMat(rota_.x);
	matRota *= ConvertRotationYAxisMat(rota_.y);
	
	matTrans = ConvertTranslationMat(pos_);

	m_ = MatIdentity();
	m_ *= matScale * matRota * matTrans;
	if (parent_) { m_ *= *parent_; }
}

void YTransform::UpdateMatrix(const Status& status)
{
	// �v�Z�p
	Vector3 p, r, s;
	
	// ���Z���đ��
	p = pos_ + status.pos_;
	r = rota_ + status.rota_;
	s = scale_ + status.scale_;

	// �A�t�B���ϊ�
	Matrix4 matScale, matRota, matTrans;
	matScale = matRota = matTrans = MatIdentity();

	matScale = ConvertScalingMat(s);

	matRota *= ConvertRotationZAxisMat(r.z);
	matRota *= ConvertRotationXAxisMat(r.x);
	matRota *= ConvertRotationYAxisMat(r.y);

	matTrans = ConvertTranslationMat(p);

	m_ = MatIdentity();
	m_ *= matScale * matRota * matTrans;
	if (parent_) { m_ *= *parent_; }
}
