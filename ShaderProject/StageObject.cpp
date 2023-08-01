#include "StageObject.h"
#include "Stage.h"

DirectX::XMFLOAT3* StageObject::m_pParentPos;

StageObject::StageObject(int x, int y, DirectX::XMFLOAT3* pPos)
{
	m_pParentPos = pPos;

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
}