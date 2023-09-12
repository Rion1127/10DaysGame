#include "ParticleManager.h"
#include "PipelineManager.h"

ParticleManager* ParticleManager::GetInstance()
{
	static ParticleManager instance;
	return &instance;
}

ParticleManager::ParticleManager()
{
}

void ParticleManager::Update()
{
	std::list<std::shared_ptr<IEmitter>>::iterator itr;
	for (itr = emitters_.begin(); itr != emitters_.end();)
	{
		//�p�[�e�B�N���̐���0�ɂȂ�����
		if ((*itr)->particle->GetParticleNum() == 0) {
			itr = emitters_.erase(itr);
			continue;
		}

		if ((*itr)->isActive) {
			//���W���X�V
			(*itr)->popCoolTime_.AddTime(1);
			if ((*itr)->popCoolTime_.GetIsEnd()) {
				(*itr)->particle->Add();

				(*itr)->popCoolTime_.Reset();
			}
		}

		(*itr)->particle->Update();
		itr++;
	}

	std::list<std::shared_ptr<IParticle2D>>::iterator itr2D;
	for (itr2D = emitters2D_.begin(); itr2D != emitters2D_.end();)
	{
		//�p�[�e�B�N���̐���0�ɂȂ�����
		if ((*itr2D)->GetIsDelete() == true) {
			itr2D = emitters2D_.erase(itr2D);
			continue;
		}

		
		(*itr2D)->Update();
		itr2D++;
	}
}

void ParticleManager::Draw()
{
	std::string shaderName = "Particle";
	
	for (auto& emitter : emitters_)
	{
		PipelineManager::PreDraw(emitter->particle->GetShaderName(), POINTLIST, emitter->particle->GetPipelineState());
		emitter->particle->Draw();
	}
}

void ParticleManager::DrawSprite()
{
	for (auto& emitter : emitters2D_)
	{
		emitter->Draw();
	}
}

void ParticleManager::AddParticle(std::string name, std::shared_ptr<IEmitter> emitter)
{
	emitters_.emplace_back();
	emitters_.back() = emitter;
	emitters_.back()->particle->SetEmitter(emitter.get());
	emitters_.back()->particle->Add();
}
