#include "GameScene.h"

#include "Easing.h"
#include "SceneManager.h"
#include "Collision.h"
#include "Camera.h"
#include "Texture.h"

#include <imgui.h>
#include <time.h>

GameScene::~GameScene()
{
	
}

void GameScene::Ini()
{
	sound_ = SoundManager::GetInstance();

	sprite_ = std::make_unique<Sprite>();
	sprite_->Ini();
	sprite_->SetTexture(TextureManager::GetInstance()->GetTexture("White"));

	player_ = std::make_unique<Player>();
	player_->Initialize();
}

void GameScene::Update()
{
#ifdef _DEBUG

#endif //_DEBUG

	sprite_->Update();
	player_->Update();
}

void GameScene::Draw()
{
	PipelineManager::PreDraw("Sprite", TRIANGLELIST);
	sprite_->Draw();
	player_->Draw();
	PipelineManager::PreDraw("Object3D", TRIANGLELIST);

	PipelineManager::PreDraw("Toon", TRIANGLELIST);

	PipelineManager::PreDraw("assimp", TRIANGLELIST);

	PipelineManager::PreDraw("Sprite", TRIANGLELIST);

	PipelineManager::PreDraw("Particle", POINTLIST);

}