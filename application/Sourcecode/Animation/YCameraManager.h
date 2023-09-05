#pragma once
#include "Shake.h"

class YCameraManager
{

public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// カメラシェイク
	/// </summary>
	/// <param name="swing"> : 揺れる量</param>
	/// <param name="dekey"> : 減衰量</param>
	void ShakeCamera(const float swing, const float dekey);

	/// <summary>
	/// カメラ位置取得
	/// </summary>
	/// <returns>カメラ位置</returns>
	Vector3 GetCameraPos();

public:

	/// <summary>
	/// シングルトン
	/// </summary>
	/// <returns>ポインタ</returns>
	static YCameraManager* GetInstance();

private:

	YCameraManager() = default;
	~YCameraManager() = default;
	YCameraManager(const YCameraManager&) = delete;
	const YCameraManager& operator=(const YCameraManager&) = delete;

private:

	// 位置
	Vector3 pos_;

	// 揺れ
	YMath::Shake shake_;

};

