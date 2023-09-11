#pragma once
#include "Sprite.h"
#include "Timer.h"

class Emitter2D;

class IParticle2D
{
private:
	struct Particle2D {
		std::unique_ptr<Sprite> sprite;
		bool isAlive = true;
		Timer timer;
		Vector2 addVec;
	};
protected:
	std::vector<Particle2D> particle_;
	bool isDelete_;
public:
	IParticle2D();
	~IParticle2D() {};

	void Add(uint32_t num,Vector2 pos,Vector2 addvec, Vector2 scale);
	void Update();
	void Draw();
protected:
	virtual void MoveUpdate() = 0;
public:
	bool GetIsDelete() { return isDelete_; }
};

