#include "Dice.h"
#include "ModelManager.h"
#include "Input.h"
#include "SceneGame.h"

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

	if (m_RotFlag)
	{
		m_Rot.x += 5.0f;
		m_Rot.y -= 5.0f;

		m_Num = rand() % 6 + 1;

		if (IsKeyTrigger('L'))
		{//�T�C�R����������
			NumRot();
		}

		if (IsKeyTrigger('K'))
		{//���j���[�ɖ߂�
			SceneGame::SetNextAction(SceneGame::Action::E_ACTION_MENU);
		}
	}
}

void Dice::NumRot()
{
	DirectX::XMFLOAT3 camRot = DirectX::XMFLOAT3(65.0f, 45.0f, 0.0f);
	m_RotFlag = false;
	m_Rot = camRot;

	switch (m_Num)
	{
	case 1:
		m_Rot = DirectX::XMFLOAT3(0.0f, -45.0f, 25.0f);
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
		m_Rot = DirectX::XMFLOAT3(0.0f, 135.0f, -25.0f);
		break;
	default:
		break;
	}

	SceneGame::SetMoveNum(m_Num);
}