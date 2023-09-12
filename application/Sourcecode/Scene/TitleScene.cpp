#include "TitleScene.h"

#include "Easing.h"
#include "SceneManager.h"
#include "Collision.h"
#include "Camera.h"
#include "Texture.h"
#include "DebugScene.h"
#include "WinAPI.h"

#include <imgui.h>
#include <time.h>

TitleScene::~TitleScene()
{

}

void TitleScene::Ini()
{
	sound_ = SoundManager::GetInstance();
	titleSprite_ = std::make_unique<Sprite>();
	titleSprite_->Ini();
	titleSprite_->SetTexture(TextureManager::GetInstance()->GetTexture("Title"));
	titleSprite_->SetAnchor(Vector2(0.0f, 0.0f));

	SoundManager::AllStop();
	SoundManager::Play("TitleBGM", true);
}

void TitleScene::Update()
{
#ifdef _DEBUG

#endif //_DEBUG

		if (MouseInput::GetInstance()->IsMouseTrigger(MOUSE_LEFT))
		{
			SceneManager::SetChangeStart(SceneName::Select);
			SoundManager::Play("Click_2SE", false, 1.0f);
		}
	

	titleSprite_->Update();

}

void TitleScene::Draw()
{
	PipelineManager::PreDraw("Sprite", TRIANGLELIST);
	
		titleSprite_->Draw();
	
	PipelineManager::PreDraw("Object3D", TRIANGLELIST);

	PipelineManager::PreDraw("Toon", TRIANGLELIST);

	PipelineManager::PreDraw("assimp", TRIANGLELIST);

	PipelineManager::PreDraw("Sprite", TRIANGLELIST);

	PipelineManager::PreDraw("Particle", POINTLIST);

	//DrawImGui();
}

void TitleScene::DrawImGui() {
	
}