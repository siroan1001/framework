#include "StageObject.h"
#include "Stage.h"

DirectX::XMFLOAT3* StageObject::m_pParentPos;

StageObject::StageObject(int x, int y, DirectX::XMFLOAT3* pPos)
{
    //　親の座標設定
	m_pParentPos = pPos;

    //　座標計算
    DirectX::XMFLOAT3 Center = *pPos;
    float Size = 10.0f;
    float Width = Size / Stage::SIZE;

    // グリッドの左上を計算
    float gridLeft = Center.x - (Size / 2.0f) + (Width / 2.0f);
    float gridTop = Center.y + (Size / 2.0f) - (Width / 2.0f);

    // 指定された添え字に対応する座標を計算
    float posX = gridLeft + (x * Width);
    float posY = Center.y;
    float posZ = gridTop - (y * Width); // z座標は中心のz座標と同じ

    m_Pos = DirectX::XMFLOAT3(posX, posY, posZ);

    //　モデル読み込み
    m_pModel = std::make_shared<Model>();
    m_pModel->Load("Assets/Model/stage/stage.fbx");

    ////　使用するシェーダーの種類を指定
    //m_ShaderPair.vsKind = ShaderManager::VSKind::E_VS_OBJECT;
    //m_ShaderPair.psKind = ShaderManager::PSKind::E_PS_COLOR;

    ////　カラー指定（デバッグ用）
    //int randnum[3] = { rand() % 256, rand() % 256, rand() % 256 };
    //m_ShaderPair.psBuf.Buf.ColorBuf.color.x = randnum[0] / 256.0f;
    //m_ShaderPair.psBuf.Buf.ColorBuf.color.y = randnum[1] / 256.0f;
    //m_ShaderPair.psBuf.Buf.ColorBuf.color.z = randnum[2] / 256.0f;

}

