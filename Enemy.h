#pragma once
#include "IEnemy.h"

class Enemy final:
	public IEnemy
{

public:
	Enemy(int32_t health);

	void Initialize();

	void Update()override;

	void Draw()override;
	
private:

};

