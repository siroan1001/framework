#include "SceneTitile.h"
#include "Input.h"
#include "SceneRoot.h"

GameUI* SceneTitle::m_TitleBG; 
TitleInfoUI* SceneTitle::m_InfoUI;

void SceneTitle::Init()
{
	m_TitleBG = CreateObj<GameUI>("TitleBG", eObjectTag::E_OBJ_TAG_SPRITE);
	m_TitleBG->CreateTex("Assets/Texture/title.png");
	m_TitleBG->SetPos(DirectX::XMFLOAT2(640.0f, 360.0f));
	m_TitleBG->SetSize(DirectX::XMFLOAT2(1280.0f, 720.0f));
	m_InfoUI = CreateObj<TitleInfoUI>("InfoUI", eObjectTag::E_OBJ_TAG_SPRITE);
	m_InfoUI->SetPos(DirectX::XMFLOAT2(640.0f, 360.0f));
	m_InfoUI->SetActive(false);
	m_InfoFlag = false;
}

void SceneTitle::Uninit()
{
}

void SceneTitle::Update(float tick)
{
	if (IsKeyPress('I'))
	{
		m_InfoUI->SetActive(true);
	}
	if (IsKeyPress('K'))
	{
		m_InfoUI->SetActive(false);
		m_InfoUI->ResetPage();
	}

	m_InfoUI->Update();

	if (IsKeyTrigger('L') && !m_InfoUI->GetActive())
	{
		SceneRoot::SetNextScene(SceneRoot::SceneKind::SCENE_GAME);
	}
}

void SceneTitle::Draw()
{
	m_TitleBG->Draw();
	m_InfoUI->Draw();
}