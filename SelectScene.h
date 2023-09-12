#pragma once
#include "Sprite.h"
#include "DebugCamera.h"
#include "mInput.h"
#include "mSound.h"
#include "Texture.h"
#include "IScene.h"
#include "Button.h"
class SelectScene :
    public IScene
{
private:
	std::unique_ptr<Button> tutorialButton_;
	std::unique_ptr<Button> mainGameButton_;
	std::unique_ptr<Button> endlessButton_;
	std::unique_ptr<Sprite> kanBanSprite_ = nullptr;
public:
	~SelectScene();

	void Ini()override;

	void Update()override;

	void Draw()override;
private:
};

