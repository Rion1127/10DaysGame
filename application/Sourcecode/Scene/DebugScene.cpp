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

	sprite_ = std::make_unique<Sprite>();
	sprite_->Ini();
	sprite_->SetTexture(TextureManager::GetInstance()->GetTexture("White"));
	

	panel_ = std::make_unique<Panel>();
	player_ = std::make_unique<Player>();
	player_->Initialize();
	enemy_ = std::make_unique<Enemy>();
	enemy_->Initialize();
}

void DebugScene::Update()
{
#ifdef _DEBUG

#endif // _DEBUG

	sprite_->Update();

	panel_->Update();
	player_->Update();
	enemy_->Update();
}

void DebugScene::Draw()
{
	panel_->DrawImGui();
	PipelineManager::PreDraw("Sprite", TRIANGLELIST);
	sprite_->Draw();
	player_->Draw();
	enemy_->Draw();
	panel_->DrawSprite();
	PipelineManager::PreDraw("Object3D", TRIANGLELIST);

	PipelineManager::PreDraw("Toon", TRIANGLELIST);

	PipelineManager::PreDraw("assimp", TRIANGLELIST);

	PipelineManager::PreDraw("Sprite", TRIANGLELIST);

	PipelineManager::PreDraw("Particle", POINTLIST);

}