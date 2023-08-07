#include "SceneBase.hpp"

#include "CameraGameMain.h"
#include "CameraDebug.h"

SceneBase::Objects SceneBase::m_objects;
SceneBase::Items SceneBase::m_items;
CameraBase* SceneBase::m_pCam[SceneBase::eCamType::E_CAM_TYPE_MAX];
SceneBase::eCamType SceneBase::m_CamType;

void SceneBase::init()
{
	CameraBase* Cam = CreateObj<CameraGameMain>("GameCam", eObjectTag::E_OBJ_TAG_CAM);
	Cam->SetPos(DirectX::XMFLOAT3(4.5f, 3.0f, 4.5f));
	Cam->SetLook(DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f));
	Cam->SetUp(DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f));
	m_pCam[eCamType::E_CAM_TYPE_GAME_MAIN] = Cam;
	Cam = CreateObj<CameraDebug>("GameDebugCam", eObjectTag::E_OBJ_TAG_CAM);
	m_pCam[eCamType::E_CAM_TYPE_GAME_DEBUG] = Cam;
}

void SceneBase::uninit()
{

}

SceneBase::SceneBase()
	: m_pParent(nullptr)
	, m_pSubScene(nullptr)
{

}
SceneBase::~SceneBase()
{
	// サブシーンを削除
	RemoveSubScene();

	// 削除
	Items::iterator it = m_items.begin();
	while (it != m_items.end())
	{
		m_objects.erase(*it);
		++it;
	}
	m_items.clear();

	// 親の参照を削除
	if(m_pParent)
		m_pParent->m_pSubScene = nullptr;
}
void SceneBase::_update(float tick)
{
	if (m_pSubScene)
		m_pSubScene->_update(tick);
	Update(tick);
}
void SceneBase::_draw()
{
	if (m_pSubScene)
		m_pSubScene->_draw();
	Draw();
}

/// @brief サブシーンの削除
void SceneBase::RemoveSubScene()
{
	// 削除するサブシーンが存在するか
	if (!m_pSubScene) return;

	// 階層内のサブシーンを優先して削除
	m_pSubScene->RemoveSubScene();

	// 直下のサブシーンを削除
	m_pSubScene->Uninit();
	delete m_pSubScene;
	m_pSubScene = nullptr;
}

void SceneBase::DestroyObj(const char* name)
{
	m_objects.erase(name);
	m_items.remove(name);
}