#pragma once
#include "Sprite.h"
#include "DebugCamera.h"
#include "mInput.h"
#include "mSound.h"
#include "Texture.h"
#include "IScene.h"
#include "Panel.h"
#include "Mino.h"
#include "Player.h"
#include "Enemy.h"
#include "MainGameSyste.h"
#include "Number.h"

class DebugScene final:
    public IScene
{
private:
	SoundManager* sound_ = nullptr;
	DebugCamera debugCamera_;

	std::unique_ptr<MainGameSyste> mainSystem_;
	std::unique_ptr<Player> player_ = nullptr;
	MinoList minoList_;

	Sprite dotSprite_;

	std::unique_ptr<Number> numberSprite_;
public:
	~DebugScene();

	void Ini()override;

	void Update()override;

	void Draw()override;
private:
};

