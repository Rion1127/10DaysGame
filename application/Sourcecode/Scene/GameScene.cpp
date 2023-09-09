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

	mainSystem_ = std::make_unique<MainGameSyste>();
	player_ = std::make_unique<Player>();
	player_->Initialize();

	mainSystem_->SetPlayer(player_.get());
}

void GameScene::Update()
{
#ifdef _DEBUG

#endif //_DEBUG

	mainSystem_->Update();
	if (mainSystem_->GetGameState() != MainGameSyste::State::PAUSE) {
		player_->Update();
	}
}

void GameScene::Draw()
{
	PipelineManager::PreDraw("Sprite", TRIANGLELIST);
	mainSystem_->DrawSprite();
	player_->Draw();
	mainSystem_->DrawSpriteFront();
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