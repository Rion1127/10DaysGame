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

	kanBanSprite_ = std::make_unique<Sprite>();
	kanBanSprite_->Ini();
	kanBanSprite_->SetTexture(TextureManager::GetInstance()->GetTexture("KanBan"));
	kanBanSprite_->SetAnchor(Vector2(0.0f, 0.0f));

	Vector2 tutorialPos = {
		WinAPI::GetWindowSize().x / 4.f,
		WinAPI::GetWindowSize().y / 1.2f,
	};
	Vector2 mainGamePos;
	mainGamePos = {
		WinAPI::GetWindowSize().x / 2.f,
		WinAPI::GetWindowSize().y / 1.2f,
	};
	Vector2 endlessPos;
	endlessPos = {
		WinAPI::GetWindowSize().x / 1.3f,
		WinAPI::GetWindowSize().y / 1.2f,
	};
	tutorialButton_ = std::make_unique<Button>(tutorialPos);
	tutorialButton_->SetTexture(TextureManager::GetInstance()->GetTexture("TutorialButton"));
	mainGameButton_ = std::make_unique<Button>(mainGamePos);
	mainGameButton_->SetTexture(TextureManager::GetInstance()->GetTexture("GameStartButton"));
	endlessButton_ = std::make_unique<Button>(endlessPos);
	endlessButton_->SetTexture(TextureManager::GetInstance()->GetTexture("EndlessButton"));

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
			SoundManager::Play("Click_2SE", false, 1.0f);
		}
	}
	else if (type_ == TitleType::StageSelect)
	{
		//選択したシーンに切り替える
		if (MouseInput::GetInstance()->IsMouseTrigger(MOUSE_LEFT))
		{
			//チュートリアルへ
			if (tutorialButton_->GetIsCollision())
			{
				SceneManager::SetChangeStart(SceneName::Tutorial);
				SceneManager::SetGameMode(GameMode::Tutorial);
				SoundManager::Play("Click_2SE", false, 1.0f);
			}
			//本編へ
			else if (mainGameButton_->GetIsCollision())
			{
				SceneManager::SetChangeStart(SceneName::Game);
				SceneManager::SetGameMode(GameMode::MainGame);
				SoundManager::Play("Click_2SE", false, 1.0f);
			}
			//エンドレスへ
			else if (mainGameButton_->GetIsCollision())
			{
				SceneManager::SetChangeStart(SceneName::Game);
				SceneManager::SetGameMode(GameMode::EndLess);
				SoundManager::Play("Click_2SE", false, 1.0f);
			}
		}

		
	}

	titleSprite_->Update();
	kanBanSprite_->Update();

	tutorialButton_->Update();
	mainGameButton_->Update();
	endlessButton_->Update();
}

void TitleScene::Draw()
{
	PipelineManager::PreDraw("Sprite", TRIANGLELIST);
	if(type_ == TitleType::Title)
	{
		titleSprite_->Draw();
	}
	else if (type_ == TitleType::StageSelect)
	{
		kanBanSprite_->Draw();
		tutorialButton_->Draw();
		mainGameButton_->Draw();
		endlessButton_->Draw();
	}
	PipelineManager::PreDraw("Object3D", TRIANGLELIST);

	PipelineManager::PreDraw("Toon", TRIANGLELIST);

	PipelineManager::PreDraw("assimp", TRIANGLELIST);

	PipelineManager::PreDraw("Sprite", TRIANGLELIST);

	PipelineManager::PreDraw("Particle", POINTLIST);

	//DrawImGui();
}

void TitleScene::DrawImGui() {
	ImGui::Begin("Scene");


	std::string type = "type : ";
	if (type_ == TitleType::Title) type += "Title";
	if (type_ == TitleType::StageSelect)type += "StageSelect";
	ImGui::Text(type.c_str());

	ImGui::End();
}