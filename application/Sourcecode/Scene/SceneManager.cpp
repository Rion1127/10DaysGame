#include "SceneManager.h"
#include "WinAPI.h"
#include "Texture.h"
#include "Easing.h"

#include "DebugScene.h"
#include "GameScene.h"
#include "TitleScene.h"

std::unique_ptr<IScene> SceneManager::scurrentScene_ = nullptr;
SceneName SceneManager::ssceneName_;
bool SceneManager::sisSetNext_ = false;
Timer SceneManager::animeTimer_;
GameMode SceneManager::sgameMode_;

void SceneManager::Ini()
{
#ifdef _DEBUG
	//ビルド開始時のシーン
	Transition<TitleScene>();
#else
	//ビルド開始時のシーン
	Transition<GameScene>();
#endif // _DEBUG

	
	


	animeTimer_.SetLimitTime(100);
	
}

void SceneManager::Update()
{
	scurrentScene_->Update();

#ifdef _DEBUG
	if (Key::TriggerKey(DIK_1)) {
		Transition<TitleScene>();
	}
	if (Key::TriggerKey(DIK_2)) {
		Transition<GameScene>();
	}
	if (Key::TriggerKey(DIK_3)) {
		//Transition<GameOverScene>();
	}
	if (Key::TriggerKey(DIK_0)) {
		Transition<DebugScene>();
	}

#endif // _DEBUG

	//切り替えアニメーション開始
	if (sisSetNext_)
	{
		animeTimer_.AddTime(1);
		
		//シーン遷移
		if (animeTimer_.GetIsEnd())
		{
			SceneChange();
		}
	}
	else
	{
		if (animeTimer_.GetTimer() > 0)
		{
			animeTimer_.AddTime(-1);
		}
	}
}

void SceneManager::Draw()
{
	//ゲーム描画
	scurrentScene_->Draw();

	PipelineManager::PreDraw("Sprite",TRIANGLELIST);
}

void SceneManager::SceneChange()
{
	if (ssceneName_ == SceneName::Title)
	{
		Transition<TitleScene>();
	}
	else if (ssceneName_ == SceneName::Game)
	{
		Transition<GameScene>();
	}
	else if (ssceneName_ == SceneName::Debug)
	{
		Transition<DebugScene>();
	}

	sisSetNext_ = false;

}

void SceneManager::SetChangeStart(const SceneName sceneName) {
	if (sisSetNext_ == false)
	{

		ssceneName_ = sceneName;
		sisSetNext_ = true;

		//ゲームシーンへ
		if (sceneName == SceneName::Game)
		{
			animeTimer_.SetLimitTime(100);
		}
	}
}
