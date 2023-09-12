#pragma once
#include "IParticle.h"
#include "IParticle2D.h"
#include <unordered_map>
#include <list>

class ParticleManager
{
private:
	std::list<std::shared_ptr<IEmitter>> emitters_;
	std::list<std::shared_ptr<IParticle2D>> emitters2D_;
public:
	static ParticleManager* GetInstance();

	void Update();

	void Draw();
	void DrawSprite();

	void AddParticle(std::string name, std::shared_ptr<IEmitter> emitter);
	
	void AllClear() { emitters_.clear();};
private:
	ParticleManager();
};

