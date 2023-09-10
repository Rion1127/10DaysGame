#include "TutorialScene.h"
#include "Easing.h"
#include "SceneManager.h"
#include "Collision.h"
#include "Camera.h"
#include "Texture.h"

#include <imgui.h>
#include <time.h>

TutorialScene::~TutorialScene()
{

}

void TutorialScene::Ini()
{
	sound_ = SoundManager::GetInstance();

	mainSystem_ = std::make_unique<MainGameSyste>();
	player_ = std::make_unique<Player>();
	player_->Initialize();

	mainSystem_->SetPlayer(player_.get());
	mainSystem_->TutorialInit();

	
}

void TutorialScene::Update()
{
#ifdef _DEBUG

#endif //_DEBUG

	mainSystem_->TutorialUpdate();
	if (mainSystem_->GetGameState() != MainGameSyste::State::PAUSE) {
		player_->Update();
	}

	
}

void TutorialScene::Draw()
{
	PipelineManager::PreDraw("Sprite", TRIANGLELIST);
	mainSystem_->TutorialDraw();
	player_->Draw();
	mainSystem_->TutorialDrawFront();
	

	PipelineManager::PreDraw("Object3D", TRIANGLELIST);

	PipelineManager::PreDraw("Toon", TRIANGLELIST);

	PipelineManager::PreDraw("assimp", TRIANGLELIST);

	PipelineManager::PreDraw("Sprite", TRIANGLELIST);

	PipelineManager::PreDraw("Particle", POINTLIST);

#ifdef _DEBUG
	mainSystem_->DrawImGui();
	mainSystem_->TutorialDrawImGui();
	player_->DrawImGui();
#endif // _DEBUG
}