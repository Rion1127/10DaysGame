#pragma once
#include "NumberDrawer.h"

namespace YGame
{
	class AnimationManager
	{

	public:

		void EmitDamage(const YTransform::Status& status, const int32_t damage);
	
	public:

		/// <summary>
		/// �V���O���g���C���X�^���X
		/// </summary>
		/// <returns>�|�C���^</returns>
		AnimationManager* GetInstance();

	private:

		AnimationManager() = default;
		~AnimationManager() = default;
		AnimationManager(const AnimationManager&) = delete;
		const AnimationManager& operator=(const AnimationManager&) = delete;

	private:

		std::array<NumberDrawer, 4> damageDrawers_;

	};
}
