#pragma once

class AnimeManager
{

public:

	/// <summary>
	/// シングルトン
	/// </summary>
	/// <returns>ポインタ</returns>
	static AnimeManager* GetInstance();

private:

	AnimeManager() = default;
	~AnimeManager() = default;
	AnimeManager(const AnimeManager&) = delete;
	const AnimeManager& operator=(const AnimeManager&) = delete;

};

