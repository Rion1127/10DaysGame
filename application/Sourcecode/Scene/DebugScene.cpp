#include "DebugScene.h"

#include "Easing.h"
#include "SceneManager.h"
#include "Collision.h"
#include "Camera.h"
#include "Texture.h"

#include <imgui.h>
#include <time.h>

DebugScene::~DebugScene()
{

}

void DebugScene::Ini()
{
	sound_ = SoundManager::GetInstance();

	sprite_ = std::make_unique<Sprite>();
	sprite_->Ini();
	sprite_->SetTexture(TextureManager::GetInstance()->GetTexture("White"));
}

void DebugScene::Update()
{
#ifdef _DEBUG

#endif // _DEBUG

	sprite_->Update();
}

void DebugScene::Draw()
{
	PipelineManager::PreDraw("Sprite", TRIANGLELIST);
	sprite_->Draw();
	PipelineManager::PreDraw("Object3D", TRIANGLELIST);

	PipelineManager::PreDraw("Toon", TRIANGLELIST);

	PipelineManager::PreDraw("assimp", TRIANGLELIST);

	PipelineManager::PreDraw("Sprite", TRIANGLELIST);

	PipelineManager::PreDraw("Particle", POINTLIST);

}