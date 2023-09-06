#include "TitleScene.h"

#include "Easing.h"
#include "SceneManager.h"
#include "Collision.h"
#include "Camera.h"
#include "Texture.h"
#include "DebugScene.h"

#include <imgui.h>
#include <time.h>

TitleScene::~TitleScene()
{
	
}

void TitleScene::Ini()
{
	sound_ = SoundManager::GetInstance();

	
}

void TitleScene::Update()
{
#ifdef _DEBUG

#endif //_DEBUG
	if (type_ == TitleType::Title)
	{
		if (MouseInput::GetInstance()->IsMouseTrigger(MOUSE_LEFT))
		{
			type_ = TitleType::StageSelect;
		}
	}
	else if (type_ == TitleType::StageSelect)
	{
		//‘I‘ð‚µ‚½ƒV[ƒ“‚ÉØ‚è‘Ö‚¦‚é
		if (MouseInput::GetInstance()->IsMouseTrigger(MOUSE_LEFT))
		{
			SceneManager::SetChangeStart(SceneName::Debug);
		}
	}
}

void TitleScene::Draw()
{
	PipelineManager::PreDraw("Sprite", TRIANGLELIST);
	

	PipelineManager::PreDraw("Object3D", TRIANGLELIST);

	PipelineManager::PreDraw("Toon", TRIANGLELIST);

	PipelineManager::PreDraw("assimp", TRIANGLELIST);

	PipelineManager::PreDraw("Sprite", TRIANGLELIST);

	PipelineManager::PreDraw("Particle", POINTLIST);

	DrawImGui();
}

void TitleScene::DrawImGui() {
	ImGui::Begin("Scene");


	std::string type = "type : ";
	if (type_ == TitleType::Title) type += "Title";
	if (type_ == TitleType::StageSelect)type += "StageSelect";
	ImGui::Text(type.c_str());

	ImGui::End();
}