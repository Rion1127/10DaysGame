#include "IParticle2D.h"

IParticle2D::IParticle2D()
{
	isDelete_ = false;
}

void IParticle2D::Add(uint32_t num, Vector2 pos, Vector2 addvec, Vector2 scale)
{
	for (uint32_t i = 0; i < num; i++) {
		Particle2D newParticle;
		newParticle.sprite = std::make_unique<Sprite>();
		newParticle.sprite->Ini();
		newParticle.sprite->SetPos(pos);
		newParticle.sprite->SetScale(scale);
		newParticle.isAlive = true;
		newParticle.addVec = addvec;
	}
}

void IParticle2D::Update()
{
	MoveUpdate();

	for (uint32_t i = 0; i < particle_.size(); i++) {
		if (particle_[i].isAlive == false) {
			particle_.erase(particle_.begin() + i);
			continue;
		}
		particle_[i].sprite->Update();
	}
}

void IParticle2D::Draw()
{
	for (uint32_t i = 0; i < particle_.size(); i++) {
		particle_[i].sprite->Draw();
	}
}
