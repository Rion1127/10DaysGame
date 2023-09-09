#include "Sprite.h"
#include "DebugCamera.h"
#include "mInput.h"
#include "mSound.h"
#include "Texture.h"
#include "IScene.h"
#include "Button.h"
#include "TransitionDrawer.h"

class TitleScene final :
	public IScene
{
private:
	enum class TitleType {
		Title,
		StageSelect
	};
private:
	SoundManager* sound_ = nullptr;
	DebugCamera debugCamera_;

	TitleType type_;
	std::unique_ptr<Button> tutorialButton_;
	std::unique_ptr<Button> mainGameButton_;
	std::unique_ptr<Button> endlessButton_;

	YGame::TransitionDrawer transition_;
public:
	~TitleScene();

	void Ini()override;

	void Update()override;

	void Draw()override;
private:
	void DrawImGui();
};

