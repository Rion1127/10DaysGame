#pragma once

class AnimeManager
{

public:

	/// <summary>
	/// �V���O���g��
	/// </summary>
	/// <returns>�|�C���^</returns>
	static AnimeManager* GetInstance();

private:

	AnimeManager() = default;
	~AnimeManager() = default;
	AnimeManager(const AnimeManager&) = delete;
	const AnimeManager& operator=(const AnimeManager&) = delete;

};

