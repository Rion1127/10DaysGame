#pragma once
#include <memory>
#include "IScene.h"
#include "mInput.h"
#include "Sprite.h"
#include "DirectX.h"
#include "Util.h"
#include "Timer.h"
#include "TransitionDrawer.h"
#include "mSound.h"

enum class SceneName {
	Title,
	Select,
	Game,
	Debug,
	Tutorial,
	None
};

enum class GameMode {
	Tutorial,
	MainGame,
	EndLess
};

class SceneManager
{
private:
	static std::unique_ptr<IScene> scurrentScene_;

	static SceneName ssceneName_;
	static bool sisSetNext_;
	static Timer animeTimer_;
	static GameMode sgameMode_;
	
	static YGame::TransitionDrawer transitionDrawer_;
	static bool isTransitionStart_;
public:
	static void Ini();
	static void Update();
	static void Draw();

	template <class NextScene>
	static inline void Transition() {
		scurrentScene_.reset();
		scurrentScene_ = std::move(std::make_unique<NextScene>());
		scurrentScene_->Ini();
	}
	static void SetChangeStart(const SceneName sceneName);
	static void SetGameMode(const GameMode gameMode) { sgameMode_ = gameMode; };
public:
	static bool GetIsSetNext() { return sisSetNext_; }
private:
	static void SceneChange();
};



