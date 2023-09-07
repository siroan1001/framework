#include "SceneTitile.h"
#include "Input.h"
#include "SceneRoot.h"

GameUI* SceneTitle::m_TitleBG;

void SceneTitle::Init()
{
	m_TitleBG = CreateObj<GameUI>("TitleBG", eObjectTag::E_OBJ_TAG_SPRITE);
	m_TitleBG->CreateTex("Assets/Texture/title.png");
	m_TitleBG->SetPos(DirectX::XMFLOAT2(640.0f, 360.0f));
	m_TitleBG->SetSize(DirectX::XMFLOAT2(1280.0f, 720.0f));
}

void SceneTitle::Uninit()
{
}

void SceneTitle::Update(float tick)
{
	if (IsKeyTrigger('L'))
	{
		SceneRoot::SetNextScene(SceneRoot::SceneKind::SCENE_GAME);
	}
}

void SceneTitle::Draw()
{
	m_TitleBG->Draw();
}