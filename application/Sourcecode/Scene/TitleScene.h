#include "Sprite.h"
#include "DebugCamera.h"
#include "mInput.h"
#include "mSound.h"
#include "Texture.h"
#include "IScene.h"
#include "Button.h"
#include "Timer.h"

#include "TitleDrawer.h"

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

	YGame::TitleDrawer titleDra_;

	std::unique_ptr<Sprite> titleSprite_ = nullptr;
	std::unique_ptr<Sprite> clickSprite_ = nullptr;
	Timer timer_;
public:
	~TitleScene();

	void Ini()override;

	void Update()override;

	void Draw()override;
private:
	void DrawImGui();
};

