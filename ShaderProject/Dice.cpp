#include "Dice.h"
#include "ModelManager.h"
#include "Input.h"
#include "SceneGame.h"
#include "Timer.h"
#include "SceneRoot.h"

Dice::Dice() : m_Num(0), m_RotFlag(true)
{
	m_pModel = ModelManager::GetModel(ModelManager::ModelKind::E_MODEL_KIND_DICE);
}

Dice::~Dice()
{
}

void Dice::Update()
{
	if (!m_Use)	return; 
	
	bool AIflag = SceneGame::GetObj<Player>(SceneGame::GetPlayerName())->GetAIFlag();

	

	if (!AIflag)
	{
		if (m_RotFlag)
		{
			m_Rot.x += 5.0f;
			m_Rot.y -= 5.0f;

			m_Num = rand() % 6 + 1;
			//m_Num = 2;

			if (IsKeyTrigger('L'))
			{//サイコロをたたく
				SceneRoot::PlayMusic("Assets/Music/SE/決定ボタンを押す13.wav", false);
				NumRot();
			}

			if (IsKeyTrigger('K'))
			{//メニューに戻る
				SceneRoot::PlayMusic("Assets/Music/SE/botan_b16.wav", false);
				SceneGame::SetNextAction(SceneGame::Action::E_ACTION_MENU);
			}
		}
	}
	else
	{
		if (!Timer::IsUsed())	Timer::StartTimer(0.6f);
		if (m_RotFlag)
		{
			m_Rot.x += 5.0f;
			m_Rot.y -= 5.0f;

			m_Num = rand() % 6 + 1;

			if (Timer::IsTimeElapsed())
			{//サイコロをたたく
				SceneRoot::PlayMusic("Assets/Music/SE/決定ボタンを押す13.wav", false);
				NumRot();
			}
		}
	}
}

void Dice::Reset()
{
	m_Num = 0;
	m_RotFlag = true;
}

void Dice::NumRot()
{
	DirectX::XMFLOAT3 camRot = DirectX::XMFLOAT3(68.0f, 45.0f, 0.0f);
	m_RotFlag = false;
	m_Rot = camRot;

	switch (m_Num)
	{
	case 1:
		m_Rot = DirectX::XMFLOAT3(0.0f, -45.0f, 22.0f);
		break;
	case 2:
		m_Rot.x += 180.0f;
		break;
	case 3:
		m_Rot.x += 90.0f;
		break;
	case 4:
		m_Rot.x -= 90.0f;
		break;
	case 5:
		break;
	case 6:
		m_Rot = DirectX::XMFLOAT3(0.0f, 135.0f, -22.0f);
		break;
	default:
		break;
	}

	SceneGame::SetMoveNum(m_Num);
}
