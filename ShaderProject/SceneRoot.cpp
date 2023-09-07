#include "SceneRoot.h"
#include <stdio.h>
#include "MoveLight.h"
#include "Model.h"
#include "Input.h"
#include "Geometory.h"
#include "Timer.h"
#include <time.h>
#include "Fade.h"
#include "CameraGameMain.h"
#include "CameraDebug.h"

#include "SceneTitile.h"
#include "SceneGame.h"

#include "ShaderManager.h"
#include "ModelManager.h"

SceneRoot::SceneKind SceneRoot::m_index; 
SceneRoot::SceneKind SceneRoot::m_nextindex;

void SceneRoot::ChangeScene()
{
	switch (m_index)
	{
	default:
	case SCENE_TITLE: AddSubScene<SceneTitle>(); break;
	case SCENE_GAME: AddSubScene<SceneGame>(); break;
	}
}

//--- 構造体
// @brief シーン情報保存
struct ViewSetting
{
	DirectX::XMFLOAT3 camPos;
	DirectX::XMFLOAT3 camLook;
	DirectX::XMFLOAT3 camUp;
	float lightRadXZ;
	float lightRadY;
	float lightH;
	float lightSV;
	int index;
};
const char* SettingFileName = "Assets/setting.dat";

void SceneRoot::Init()
{
	// 保存データの読み込み
	ViewSetting setting =
	{
		DirectX::XMFLOAT3(0.0f, 1.0f, -5.0f),
		DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f),
		DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f),
		0.0f, DirectX::XM_PIDIV4,
		0.0f, 1.0f,
		SCENE_GAME
	};

	srand((unsigned int)time(NULL));

	//全シーンで共通して使うものを作成

	// カメラの作成
	CameraBase* Cam = CreateObj<CameraGameMain>("GameCam", eObjectTag::E_OBJ_TAG_CAM);
	Cam->SetPos(DirectX::XMFLOAT3(3.75f, 3.0f, 3.75f));
	Cam->SetLook(DirectX::XMFLOAT3(-1.5f, 0.0f, -1.5f));
	Cam->SetUp(DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f));
	m_pCam[eCamType::E_CAM_TYPE_GAME_MAIN] = Cam;
	Cam = CreateObj<CameraDebug>("GameDebugCam", eObjectTag::E_OBJ_TAG_CAM);
	m_pCam[eCamType::E_CAM_TYPE_GAME_DEBUG] = Cam;

	// ライトの作成
	MoveLight* pLight = CreateObj<MoveLight>("Light", eObjectTag::E_OBJ_TAG_LIGHT);
	pLight->SetRot(setting.lightRadXZ, setting.lightRadY);
	pLight->SetHSV(setting.lightH, setting.lightSV);
	pLight->UpdateParam();

	// フェードの作成
	Fade* pFade = CreateObj<Fade>("Fade", eObjectTag::E_OBJ_TAG_SPRITE);
	pFade->SetPos(DirectX::XMFLOAT2(640.0f, 360.0f));

	ShaderManager& ShaderMana = ShaderManager::GetInstance();
	ModelManager& ModelMana = ModelManager::GetInstance();

	Timer::Init();

	SceneBase::init();

	// シーンの作成
	m_index = SCENE_TITLE;
	m_nextindex = m_index;
	ChangeScene();
}

void SceneRoot::Uninit()
{
	SceneBase::uninit();
}

void SceneRoot::Update(float tick)
{
	CameraBase* pCamera = GetObj<CameraBase>("Camera");
	LightBase* pLight = GetObj<LightBase>("Light");
	Fade* pFade = GetObj<Fade>("Fade");

	if (m_nextindex != m_index)
	{
		pFade->StartFade();
	}

	pFade->Update();

	if (pFade->GetFadeState() == Fade::FADE_END)
	{
		m_index = m_nextindex;
		RemoveSubScene();
		ChangeScene();
		pFade->EndFade();
	}
}
void SceneRoot::Draw()
{
	CameraBase* pCamera = GetCamera();
	LightBase* pLight = GetObj<LightBase>("Light");
	Fade* pFade = GetObj<Fade>("Fade");

	DirectX::XMFLOAT4X4 fmat;
	DirectX::XMStoreFloat4x4(&fmat, DirectX::XMMatrixIdentity());
	Geometory::SetWorld(fmat);
	Geometory::SetView(pCamera->GetView());
	Geometory::SetProjection(pCamera->GetProj());

	// 網掛け描画
	const int GridSize = 10;
	Geometory::SetColor(DirectX::XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f));
	for (int i = 1; i <= GridSize; ++i)
	{
		float g = (float)i;
		Geometory::AddLine(DirectX::XMFLOAT3(g, 0.0f, -GridSize), DirectX::XMFLOAT3(g, 0.0f, GridSize));
		Geometory::AddLine(DirectX::XMFLOAT3(-g, 0.0f, -GridSize), DirectX::XMFLOAT3(-g, 0.0f, GridSize));
		Geometory::AddLine(DirectX::XMFLOAT3(-GridSize, 0.0f, g), DirectX::XMFLOAT3(GridSize, 0.0f, g));
		Geometory::AddLine(DirectX::XMFLOAT3(-GridSize, 0.0f, -g), DirectX::XMFLOAT3(GridSize, 0.0f, -g));
	}
	// 軸描画
	Geometory::SetColor(DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
	Geometory::AddLine(DirectX::XMFLOAT3(-GridSize, 0.0f, 0.0f), DirectX::XMFLOAT3(GridSize, 0.0f, 0.0f));
	Geometory::SetColor(DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
	Geometory::AddLine(DirectX::XMFLOAT3(0.0f, -GridSize, 0.0f), DirectX::XMFLOAT3(0.0f, GridSize, 0.0f));
	Geometory::SetColor(DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f));
	Geometory::AddLine(DirectX::XMFLOAT3(0.0f, 0.0f, -GridSize), DirectX::XMFLOAT3(0.0f, 0.0f, GridSize));

	Geometory::DrawLines();

	// オブジェクト描画
	pCamera->Draw();
	pLight->Draw();
	pFade->Draw();
}

void SceneRoot::SetNextScene(SceneKind kind)
{
	m_nextindex = kind;
}
