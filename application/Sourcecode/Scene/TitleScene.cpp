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

	Vector2 tutorialPos = {
		WinAPI::GetWindowSize().x / 4.f,
		WinAPI::GetWindowSize().y / 1.2f,
	};
	Vector2 mainGamePos;
	mainGamePos = {
		WinAPI::GetWindowSize().x / 1.5f,
		WinAPI::GetWindowSize().y / 1.2f,
	};
	Vector2 endlessPos;
	tutorialButton_ = std::make_unique<Button>(tutorialPos, 0);
	tutorialButton_->SetTexture(TextureManager::GetInstance()->GetTexture("TutorialButton"));
	mainGameButton_ = std::make_unique<Button>(mainGamePos, 0);
	mainGameButton_->SetTexture(TextureManager::GetInstance()->GetTexture("GameStartButton"));
	endlessButton_ = std::make_unique<Button>(endlessPos, 0);
}

void TitleScene::Update()
{
#ifdef _DEBUG

#endif //_DEBUG
	if (type_ == TitleType::Title)
	{
		if (MouseInput::GetInstance()->IsMouseTrigger(MOUSE_LEFT))
		{
			type_ = TitleType::StageSelect;
		}
	}
	else if (type_ == TitleType::StageSelect)
	{
		//‘I‘ð‚µ‚½ƒV[ƒ“‚ÉØ‚è‘Ö‚¦‚é
		if (MouseInput::GetInstance()->IsMouseTrigger(MOUSE_LEFT))
		{
			if (tutorialButton_->GetIsCollision())
			{
				SceneManager::SetChangeStart(SceneName::Debug);
			}else if (mainGameButton_->GetIsCollision())
			{
				SceneManager::SetChangeStart(SceneName::Game);
			}
		}

		
	}

	tutorialButton_->Update();
	mainGameButton_->Update();
}

void TitleScene::Draw()
{
	PipelineManager::PreDraw("Sprite", TRIANGLELIST);
	if (type_ == TitleType::StageSelect)
	{
		tutorialButton_->Draw();
		mainGameButton_->Draw();
	}
	PipelineManager::PreDraw("Object3D", TRIANGLELIST);

	PipelineManager::PreDraw("Toon", TRIANGLELIST);

	PipelineManager::PreDraw("assimp", TRIANGLELIST);

	PipelineManager::PreDraw("Sprite", TRIANGLELIST);

	PipelineManager::PreDraw("Particle", POINTLIST);

	DrawImGui();
}

void TitleScene::DrawImGui() {
	ImGui::Begin("Scene");


	std::string type = "type : ";
	if (type_ == TitleType::Title) type += "Title";
	if (type_ == TitleType::StageSelect)type += "StageSelect";
	ImGui::Text(type.c_str());

	ImGui::End();
}