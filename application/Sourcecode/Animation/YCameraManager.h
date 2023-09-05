#pragma once
#include "Shake.h"

class YCameraManager
{

public:

	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �J�����V�F�C�N
	/// </summary>
	/// <param name="swing"> : �h����</param>
	/// <param name="dekey"> : ������</param>
	void ShakeCamera(const float swing, const float dekey);

	/// <summary>
	/// �J�����ʒu�擾
	/// </summary>
	/// <returns>�J�����ʒu</returns>
	Vector3 GetCameraPos();

public:

	/// <summary>
	/// �V���O���g��
	/// </summary>
	/// <returns>�|�C���^</returns>
	static YCameraManager* GetInstance();

private:

	YCameraManager() = default;
	~YCameraManager() = default;
	YCameraManager(const YCameraManager&) = delete;
	const YCameraManager& operator=(const YCameraManager&) = delete;

private:

	// �ʒu
	Vector3 pos_;

	// �h��
	YMath::Shake shake_;

};

