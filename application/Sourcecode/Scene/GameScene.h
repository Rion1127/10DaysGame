#pragma once
#include "Sprite.h"
#include "DebugCamera.h"
#include "mInput.h"
#include "mSound.h"
#include "Texture.h"
#include "IScene.h"
#include "Player.h"

class GameScene final :
	public IScene
{
private:
	SoundManager* sound_ = nullptr;
	DebugCamera debugCamera_;

	std::unique_ptr<Sprite> sprite_;
	std::unique_ptr<Player> player_ = nullptr;
public:
	~GameScene();

	void Ini()override;

	void Update()override;

	void Draw()override;
private:
};