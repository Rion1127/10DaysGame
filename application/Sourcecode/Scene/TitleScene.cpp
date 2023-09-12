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

	clickSprite_ = std::make_unique<Sprite>();
	clickSprite_->Ini();
	clickSprite_->SetTexture(TextureManager::GetInstance()->GetTexture("Click"));
	Vector2 pos = {
		WinAPI::GetWindowSize().x / 2.f,
		WinAPI::GetWindowSize().y / 1.2f
	};
	clickSprite_->SetPos(pos);

	timer_.SetLimitTime(60);
}

void TitleScene::Update()
{
#ifdef _DEBUG

#endif //_DEBUG

		if (MouseInput::GetInstance()->IsMouseTrigger(MOUSE_LEFT))
		{
			if (SceneManager::GetIsSetNext() == false) {
				SceneManager::SetChangeStart(SceneName::Select);
				SoundManager::Play("Click_2SE", false, 1.0f);
			}
		}
		timer_.AddTime(1);
		if (timer_.GetIsEnd()) {
			bool isInvisible = clickSprite_->GetIsInvisible();

			isInvisible = (isInvisible == true) ? false : true;

			clickSprite_->SetInvisivle(isInvisible);

			timer_.Reset();
		}
	//
	titleSprite_->Update();
	clickSprite_->Update();
}

void TitleScene::Draw()
{
	PipelineManager::PreDraw("Sprite", TRIANGLELIST);
	
	titleSprite_->Draw();
	clickSprite_->Draw();
	
	PipelineManager::PreDraw("Object3D", TRIANGLELIST);

	PipelineManager::PreDraw("Toon", TRIANGLELIST);

	PipelineManager::PreDraw("assimp", TRIANGLELIST);

	PipelineManager::PreDraw("Sprite", TRIANGLELIST);

	PipelineManager::PreDraw("Particle", POINTLIST);

	//DrawImGui();
}

void TitleScene::DrawImGui() {
	
}