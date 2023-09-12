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

	backGround_ = std::make_unique<Sprite>();
	backGround_->Ini();
	backGround_->SetTexture(TextureManager::GetInstance()->GetTexture("Stage1"));
	backGround_->SetAnchor(Vector2(0.0f, 0.0f));

	puzzleBackGround_ = std::make_unique<Sprite>();
	puzzleBackGround_->Ini();
	puzzleBackGround_->SetPos(Vector2(0.0f,240.0f));

	puzzleBackGround_->SetTexture(TextureManager::GetInstance()->GetTexture("Sand1"));
	puzzleBackGround_->SetAnchor(Vector2(0.0f, 0.0f));

	SoundManager::AllStop();
	SoundManager::Play("FightBGM",true);
}

void GameScene::Update()
{
#ifdef _DEBUG

#endif //_DEBUG

	mainSystem_->Update();
	if (mainSystem_->GetGameState() != MainGameSyste::State::PAUSE) {
		player_->Update();
	}

	backGround_->Update();
	puzzleBackGround_->Update();
}

void GameScene::Draw()
{
	PipelineManager::PreDraw("Sprite", TRIANGLELIST);
	backGround_->Draw();
	puzzleBackGround_->Draw();
	mainSystem_->DrawSprite();
	player_->Draw();
	mainSystem_->DrawSpriteFront();
	PipelineManager::PreDraw("Object3D", TRIANGLELIST);

	PipelineManager::PreDraw("Toon", TRIANGLELIST);

	PipelineManager::PreDraw("assimp", TRIANGLELIST);

	PipelineManager::PreDraw("Sprite", TRIANGLELIST);

	PipelineManager::PreDraw("Particle", POINTLIST);

	mainSystem_->DrawImGui();
	player_->DrawImGui();
#ifdef _DEBUG
#endif // _DEBUG
}