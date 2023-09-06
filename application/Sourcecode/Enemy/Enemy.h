#pragma once
#include "IEnemy.h"

class Enemy final:
	public IEnemy
{

public:
	Enemy(int32_t health,int32_t attackPower);
	~Enemy() {
		int a = 0;
	}
	void Initialize();

	void Update()override;

	void Draw()override;
	void DrawImGui()override;
	
private:

};

