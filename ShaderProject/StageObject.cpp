#include "StageObject.h"
#include "Stage.h"
#include "ModelManager.h"

DirectX::XMFLOAT3* StageObject::m_pParentPos;

StageObject::StageObject(int x, int y, DirectX::XMFLOAT3* pPos)
{
    //　親の座標設定
	m_pParentPos = pPos;

    //　座標計算
    DirectX::XMFLOAT3 Center = *pPos;
    float Size = 9.0f;
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
    m_pModel = ModelManager::GetModel(ModelManager::ModelKind::E_MODEL_KIND_STAGE_LV0);

    m_HuvePlayer = Player::PlayerNum::E_PLAYER_NUM_MAX;
    m_Lv = 0;
}

void StageObject::KeepStage(Player::PlayerNum playernum)
{
    m_HuvePlayer = playernum;
    m_Lv++;
	ChangeModel();
}

void StageObject::LevelUpStage()
{
	if (m_Lv < 3)
	{
		m_Lv++;
		ChangeModel();
	}
}

void StageObject::DamageStage()
{
}

void StageObject::ReleaseStage()
{
    m_HuvePlayer = Player::PlayerNum::E_PLAYER_NUM_MAX;
    m_Lv = 0;
}

void StageObject::ChangeModel()
{
	switch (m_HuvePlayer)
	{
	case Player::PlayerNum::E_PLAYER_NUM_1:
		switch (m_Lv)
		{
		case 1:
			m_pModel = ModelManager::GetModel(ModelManager::ModelKind::E_MODEL_KIND_STAGE_RED_LV1);
			break;
		case 2:
			m_pModel = ModelManager::GetModel(ModelManager::ModelKind::E_MODEL_KIND_STAGE_RED_LV2);
			break;
		case 3:
			m_pModel = ModelManager::GetModel(ModelManager::ModelKind::E_MODEL_KIND_STAGE_RED_LV3);
			break;
		}
		break;
	case Player::PlayerNum::E_PLAYER_NUM_2:
		switch (m_Lv)
		{
		case 1:
			m_pModel = ModelManager::GetModel(ModelManager::ModelKind::E_MODEL_KIND_STAGE_BLUE_LV1);
			break;
		case 2:
			m_pModel = ModelManager::GetModel(ModelManager::ModelKind::E_MODEL_KIND_STAGE_BLUE_LV2);
			break;
		case 3:
			m_pModel = ModelManager::GetModel(ModelManager::ModelKind::E_MODEL_KIND_STAGE_BLUE_LV3);
			break;
		}
		break;
	case Player::PlayerNum::E_PLAYER_NUM_MAX:
		m_pModel = ModelManager::GetModel(ModelManager::ModelKind::E_MODEL_KIND_STAGE_LV0);
	}
}

