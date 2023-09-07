#ifndef __SCENE_BASE_HPP__
#define __SCENE_BASE_HPP__

#include <memory>
#include <map>
#include <string>
#include <list>
#include <vector>
#include <Windows.h>

#include "BaseProperty.h"

#include "Player.h"
#include "CameraBase.h"

// @brief シーン追加用オブジェクト
class SceneObjectBase
{
public:
	virtual ~SceneObjectBase() {}
};

enum eObjectTag
{
	E_OBJ_TAG_CAM = 0,
	E_OBJ_TAG_LIGHT,
	E_OBJ_TAG_RTV,
	E_OBJ_TAG_DSV,
	E_OBJ_TAG_OBJ,
	E_OBJ_TAG_SPRITE,
	E_OBJ_TAG_SHEDER,
	E_OBJ_TAG_MAX,
};

template<class T>
struct ObjectStatus
{
	eObjectTag m_tag;
	std::shared_ptr<T> m_pObj;
};


template<class T>
class SceneObject : public SceneObjectBase
{
public:
	SceneObject(std::shared_ptr<T> ptr, eObjectTag tag) 
	{
		m_pObject.m_pObj = ptr;
		m_pObject.m_tag = tag;
	}
	virtual ~SceneObject() {}
	ObjectStatus<T> m_pObject;
};

// @breif シーン基本クラス
class SceneBase
{
private:
	using Objects = std::map<std::string, std::shared_ptr<SceneObjectBase>>;
	using Items = std::list<std::string>;

public:
	enum eCamType
	{
		E_CAM_TYPE_GAME_MAIN = 0,
		E_CAM_TYPE_GAME_DEBUG,
		E_CAM_TYPE_MAX,
	};

public:
	static void init();
	static void uninit();


	SceneBase();
	virtual ~SceneBase();
	void _update(float tick);
	void _draw();

	// シーン操作関数
	template<class T> T* AddSubScene();
	void RemoveSubScene();

	// オブジェクト操作関数
	template<class T> T* CreateObj(const char* name, eObjectTag tag);
	void DestroyObj(const char* name);
	template<class T> static T* GetObj(const char* name);
	template<class T> static std::list<T*> GetObjswithTag(eObjectTag tag);

	static CameraBase* GetCamera() { return m_pCam[m_CamType]; }

	// 継承シーンの一通りの処理
	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update(float tick) = 0;
	virtual void Draw() = 0;

private:
	static Objects m_objects;
	
protected:
	SceneBase* m_pParent;
	SceneBase* m_pSubScene;
	Items m_items;

	static CameraBase* m_pCam[E_CAM_TYPE_MAX];
	static eCamType m_CamType;
};

/// <summary>
/// サブシーンの追加
/// </summary>
/// <typeparam name="T">サブシーンの型</typeparam>
/// <returns>生成したサブシーン</returns>
template<class T> T* SceneBase::AddSubScene()
{
	RemoveSubScene();
	T* pScene = new T;
	m_pSubScene = pScene;
	pScene->m_pParent = this;
	pScene->Init();
	return pScene;
}

/// <summary>
/// オブジェクトの生成
/// </summary>
/// <typeparam name="T">オブジェクトの型</typeparam>
/// <param name="name">オブジェクトの名称</param>
/// <returns>生成したオブジェクト</returns>
template<class T> T* SceneBase::CreateObj(const char* name, eObjectTag tag)
{
#ifdef _DEBUG
	// デバッグ中のみ、名称ダブりがないかチェック
	Objects::iterator it = m_objects.find(name);
	if (it != m_objects.end()) {
		static char buf[256];
		sprintf_s(buf, sizeof(buf), "Failed to create object. %s", name);
		MessageBox(NULL, buf, "Error", MB_OK);
		return nullptr;
	}
#endif // _DEBUG

	// オブジェクト生成
	std::shared_ptr<T> ptr = std::make_shared<T>();
	m_objects.insert(std::pair<std::string, std::shared_ptr<SceneObjectBase>>(name, std::make_shared<SceneObject<T>>(ptr, tag)));
	m_items.push_back(name);
	return ptr.get();
}

/// <summary>
/// オブジェクトの取得
/// </summary>
/// <typeparam name="T">オブジェクトの型</typeparam>
/// <param name="name">オブジェクトの名称</param>
/// <returns>取得したオブジェクト</returns>
template<class T> T* SceneBase::GetObj(const char* name)
{
    // オブジェクトの探索
    Objects::iterator it = m_objects.find(name);
    if (it == m_objects.end()) return nullptr;

    // 型変換
    std::shared_ptr<SceneObject<T>> ptr = std::reinterpret_pointer_cast<SceneObject<T>>(it->second);
    return ptr->m_pObject.m_pObj.get();
}

template<class T> std::list<T*> SceneBase::GetObjswithTag(eObjectTag tag)
{
	std::list<T*> result;

	for (const auto& pair : m_objects)
	{
		std::shared_ptr<SceneObjectBase> objBasePtr = pair.second;
		SceneObject<T>* derivedObjPtr = static_cast<SceneObject<T>*>(objBasePtr.get());

		if (derivedObjPtr && derivedObjPtr->m_pObject.m_tag == tag)
		{
			std::shared_ptr<T> ptr = std::dynamic_pointer_cast<T>(derivedObjPtr->m_pObject.m_pObj);
			result.push_back(ptr.get());
		}
	}

	return result;
}

#endif // __SCENE_BASE_HPP__