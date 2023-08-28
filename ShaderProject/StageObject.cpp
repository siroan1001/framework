#include "StageObject.h"
#include "Stage.h"
#include "ModelManager.h"

DirectX::XMFLOAT3* StageObject::m_pParentPos;

StageObject::StageObject(int x, int y, DirectX::XMFLOAT3* pPos)
{
    //�@�e�̍��W�ݒ�
	m_pParentPos = pPos;

    //�@���W�v�Z
    DirectX::XMFLOAT3 Center = *pPos;
    float Size = 12.0f;
    float Width = Size / Stage::SIZE;

    // �O���b�h�̍�����v�Z
    float gridLeft = Center.x - (Size / 2.0f) + (Width / 2.0f);
    float gridTop = Center.y + (Size / 2.0f) - (Width / 2.0f);

    // �w�肳�ꂽ�Y�����ɑΉ�������W���v�Z
    float posX = gridLeft + (x * Width);
    float posY = Center.y;
    float posZ = gridTop - (y * Width); // z���W�͒��S��z���W�Ɠ���

    m_Pos = DirectX::XMFLOAT3(posX, posY, posZ);

    //�@���f���ǂݍ���
    m_pModel = ModelManager::GetModel(ModelManager::ModelKind::E_MODEL_KIND_STAGE);

    m_HuvePlayer = SceneGame::PlayerNum::E_PLAYER_NUM_MAX;
    m_Lv = 0;
}

void StageObject::KeepStage(SceneGame::PlayerNum playernum)
{
    m_HuvePlayer = playernum;
    m_Lv++;
    switch (m_HuvePlayer)
    {
    case SceneGame::E_PLAYER_NUM_1:
        switch (m_Lv)
        {
        case 1:
            m_pModel = ModelManager::GetModel(ModelManager::ModelKind::E_MODEL_KIND_STAGE);
            break;
        case 2:
            m_pModel = ModelManager::GetModel(ModelManager::ModelKind::E_MODEL_KIND_STAGE);
            break;
        case 3:
            m_pModel = ModelManager::GetModel(ModelManager::ModelKind::E_MODEL_KIND_STAGE);
            break;
        }
        break;
    case SceneGame::E_PLAYER_NUM_2:
        switch (m_Lv)
        {
        case 1:
            m_pModel = ModelManager::GetModel(ModelManager::ModelKind::E_MODEL_KIND_STAGE);
            break;
        case 2:
            m_pModel = ModelManager::GetModel(ModelManager::ModelKind::E_MODEL_KIND_STAGE);
            break;
        case 3:
            m_pModel = ModelManager::GetModel(ModelManager::ModelKind::E_MODEL_KIND_STAGE);
            break;
        }
        break;
    }
}

void StageObject::ReleaseStage()
{
    m_HuvePlayer = SceneGame::PlayerNum::E_PLAYER_NUM_MAX;
    m_Lv = 0;
}

