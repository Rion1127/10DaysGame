#pragma once
#include "Sprite.h"
#include "DebugCamera.h"
#include "mInput.h"
#include "mSound.h"
#include "Texture.h"
#include "IScene.h"

class DebugScene final:
    public IScene
{
private:
	SoundManager* sound_ = nullptr;
	DebugCamera debugCamera_;

	std::unique_ptr<Sprite> sprite_;
public:
	~DebugScene();

	void Ini()override;

	void Update()override;

	void Draw()override;
private:
};

