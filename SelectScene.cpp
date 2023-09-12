#include "SelectScene.h"
#include "SceneManager.h"

SelectScene::~SelectScene()
{
}

void SelectScene::Ini()
{
	kanBanSprite_ = std::make_unique<Sprite>();
	kanBanSprite_->Ini();
	kanBanSprite_->SetTexture(TextureManager::GetInstance()->GetTexture("KanBan"));
	kanBanSprite_->SetAnchor(Vector2(0.0f, 0.0f));

	Vector2 tutorialPos = {
		WinAPI::GetWindowSize().x / 3.8f,
		WinAPI::GetWindowSize().y / 2.8f,
	};
	Vector2 mainGamePos;
	mainGamePos = {
		WinAPI::GetWindowSize().x / 1.4f,
		WinAPI::GetWindowSize().y / 1.6f,
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

void SelectScene::Update()
{
	//選択したシーンに切り替える
	if (MouseInput::GetInstance()->IsMouseTrigger(MOUSE_LEFT))
	{
		if (SceneManager::GetIsSetNext() == false) {
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
		}
		////エンドレスへ
		//else if (mainGameButton_->GetIsCollision())
		//{
		//	SceneManager::SetChangeStart(SceneName::Game);
		//	SceneManager::SetGameMode(GameMode::EndLess);
		//	SoundManager::Play("Click_2SE", false, 1.0f);
		//}
	}
	kanBanSprite_->Update();

	tutorialButton_->Update();
	mainGameButton_->Update();
}

void SelectScene::Draw()
{
	PipelineManager::PreDraw("Sprite", TRIANGLELIST);
	kanBanSprite_->Draw();
	tutorialButton_->Draw();
	mainGameButton_->Draw();
}
