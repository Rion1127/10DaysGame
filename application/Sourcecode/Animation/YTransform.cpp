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
	// 行列更新
	UpdateMatrix();
}

YTransform::YTransform(const Status & status) :
	pos_(status.pos_),
	rota_(status.rota_),
	scale_(status.scale_),
	m_(MatIdentity()),
	parent_(nullptr)
{
	// 行列更新
	UpdateMatrix();
}

YTransform::Status YTransform::Status::Default()
{
	// 戻り値用
	Status result;
	
	// 初期化
	result.pos_ = Vector3(0.0f, 0.0f, 0.0f);
	result.rota_ = Vector3(0.0f, 0.0f, 0.0f);
	result.scale_ = Vector3(1.0f, 1.0f, 1.0f);

	// 返す
	return result;
}

void YTransform::Initialize(const Status& status)
{
	// 代入
	pos_ = status.pos_;
	rota_ = status.rota_;
	scale_ = status.scale_;
	
	// 行列更新
	UpdateMatrix();
}

void YTransform::UpdateMatrix()
{
	// アフィン変換
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
	// 計算用
	Vector3 p, r, s;
	
	// 加算して代入
	p = pos_ + status.pos_;
	r = rota_ + status.rota_;
	s = scale_ + status.scale_;

	// アフィン変換
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
