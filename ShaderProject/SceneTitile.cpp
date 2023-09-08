#include "SceneTitile.h"
#include "Input.h"
#include "SceneRoot.h"
#include "Startup.h"

TitleUI* SceneTitle::m_TitleBG; 
TitleInfoUI* SceneTitle::m_InfoUI;

void SceneTitle::Init()
{
	m_TitleBG = CreateObj<TitleUI>("TitleBG", eObjectTag::E_OBJ_TAG_SPRITE);
	m_TitleBG->SetPos(DirectX::XMFLOAT2(640.0f, 360.0f));
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
	m_TitleBG->Update();
	m_InfoUI->Update();

	if (IsKeyTrigger('L') && !m_InfoUI->GetActive())
	{
		switch (m_TitleBG->GetTitleState())
		{
		case TitleUI::TitleState::E_TITLE_STATE_START:
			SceneRoot::PlayMusic("Assets/Music/SE/決定ボタンを押す1.wav", false);
			SceneRoot::SetNextScene(SceneRoot::SceneKind::SCENE_GAME);
			break;
		case TitleUI::TitleState::E_TITLE_STATE_INFO:
			SceneRoot::PlayMusic("Assets/Music/SE/決定ボタンを押す1.wav", false);
			m_InfoUI->SetActive(true);
			break;
		case TitleUI::TitleState::E_TITLE_STATE_END:
			SceneRoot::PlayMusic("Assets/Music/SE/決定ボタンを押す1.wav", false);
			GameEnd();
			break;
		default:
			break;
		}
	}
	if (IsKeyPress('K') && m_InfoUI->GetActive())
	{
		SceneRoot::PlayMusic("Assets/Music/SE/botan_b16.wav", false);
		m_InfoUI->SetActive(false);
		m_InfoUI->ResetPage();
	}
}

void SceneTitle::Draw()
{
	m_TitleBG->Draw();
	m_InfoUI->Draw();
}