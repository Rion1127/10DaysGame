#pragma once
#include "Sprite.h"
#include "DebugCamera.h"
#include "mInput.h"
#include "mSound.h"
#include "Texture.h"
#include "IScene.h"
#include "Panel.h"
#include "Mino.h"

class DebugScene final:
    public IScene
{
private:
	SoundManager* sound_ = nullptr;
	DebugCamera debugCamera_;

	std::unique_ptr<Sprite> sprite_;

	std::unique_ptr<Panel> panel_;
	MinoList minoList_;
public:
	~DebugScene();

	void Ini()override;

	void Update()override;

	void Draw()override;
private:
};

