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
	//
}

void DebugScene::Ini()
{
	sound_ = SoundManager::GetInstance();
	
	mainSystem_ = std::make_unique<MainGameSyste>();
	player_ = std::make_unique<Player>();
	player_->Initialize();
	enemy_ = std::make_unique<Enemy>();
	enemy_->Initialize();
}

void DebugScene::Update()
{
#ifdef _DEBUG

#endif // _DEBUG

	mainSystem_->Update();
	player_->Update();
	enemy_->Update();
}

void DebugScene::Draw()
{
	PipelineManager::PreDraw("Sprite", TRIANGLELIST);
	player_->Draw();
	enemy_->Draw();
	mainSystem_->DrawSprite();
	PipelineManager::PreDraw("Object3D", TRIANGLELIST);

	PipelineManager::PreDraw("Toon", TRIANGLELIST);

	PipelineManager::PreDraw("assimp", TRIANGLELIST);

	PipelineManager::PreDraw("Sprite", TRIANGLELIST);

	PipelineManager::PreDraw("Particle", POINTLIST);

}