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
	
	mainSystem_->SetPlayer(player_.get());

	dotSprite_.SetTexture(TextureManager::GetInstance()->GetTexture("DotTest"));
	dotSprite_.Ini();
	dotSprite_.SetPos(Vector2(100,800));
}

void DebugScene::Update()
{
#ifdef _DEBUG

#endif // _DEBUG

	mainSystem_->Update();
	player_->Update();
	dotSprite_.Update();
}

void DebugScene::Draw()
{
	PipelineManager::PreDraw("Sprite", TRIANGLELIST);
	mainSystem_->DrawSprite();
	player_->Draw();
	dotSprite_.Draw();
	PipelineManager::PreDraw("Object3D", TRIANGLELIST);

	PipelineManager::PreDraw("Toon", TRIANGLELIST);

	PipelineManager::PreDraw("assimp", TRIANGLELIST);

	PipelineManager::PreDraw("Sprite", TRIANGLELIST);

	PipelineManager::PreDraw("Particle", POINTLIST);

#ifdef _DEBUG
	mainSystem_->DrawImGui();
	player_->DrawImGui();
#endif // _DEBUG
}