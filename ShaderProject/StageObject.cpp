#include "StageObject.h"
#include "Stage.h"

DirectX::XMFLOAT3* StageObject::m_pParentPos;

StageObject::StageObject(int x, int y, DirectX::XMFLOAT3* pPos)
{
    //�@�e�̍��W�ݒ�
	m_pParentPos = pPos;

    //�@���W�v�Z
    DirectX::XMFLOAT3 Center = *pPos;
    float Size = 10.0f;
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
    m_pModel = std::make_shared<Model>();
    m_pModel->Load("Assets/Model/stage/stage.fbx");

    ////�@�g�p����V�F�[�_�[�̎�ނ��w��
    //m_ShaderPair.vsKind = ShaderManager::VSKind::E_VS_OBJECT;
    //m_ShaderPair.psKind = ShaderManager::PSKind::E_PS_COLOR;

    ////�@�J���[�w��i�f�o�b�O�p�j
    //int randnum[3] = { rand() % 256, rand() % 256, rand() % 256 };
    //m_ShaderPair.psBuf.Buf.ColorBuf.color.x = randnum[0] / 256.0f;
    //m_ShaderPair.psBuf.Buf.ColorBuf.color.y = randnum[1] / 256.0f;
    //m_ShaderPair.psBuf.Buf.ColorBuf.color.z = randnum[2] / 256.0f;

}

