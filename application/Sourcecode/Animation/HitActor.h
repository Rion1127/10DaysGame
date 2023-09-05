#pragma once
#include "Shake.h"
#include "Color.h"
#include <cstdint>

namespace YGame
{
	class HitActor
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
		/// ��e
		/// </summary>
		/// <param name="swing"> : �h��</param>
		/// <param name="dekey"> : �����l</param>
		/// <param name="place"> : ��</param>
		void Hit(const float swing, const float dekey);

	public:
		
		/// <summary>
		/// ���쒆��
		/// </summary>
		/// <returns>����t���O</returns>
		inline bool IsAct() const { return isAct_; }

		/// <summary>
		/// �h��l�擾
		/// </summary>
		/// <returns>�h��l</returns>
		inline Vector3 ShakePosValue() const { return shake_.Value(); }

		/// <summary>
		/// �q�b�g���̐F
		/// </summary>
		/// <returns></returns>
		inline Color ColorValue() const { return colorValue_; }

	public:

		HitActor() = default;
		
		virtual ~HitActor() = default;
	
	private:

		// �����Ă��邩�t���O
		bool isAct_ = false;
		
		// �h��
		YMath::Shake shake_;

		// �F
		Color colorValue_;
	};
}
