#ifndef __SCENE_BASE_HPP__
#define __SCENE_BASE_HPP__

#include <memory>
#include <map>
#include <string>
#include <list>
#include <vector>
#include <Windows.h>

// @brief �V�[���ǉ��p�I�u�W�F�N�g
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

// @breif �V�[����{�N���X
class SceneBase
{
private:
	using Objects = std::map<std::string, std::shared_ptr<SceneObjectBase>>;
	using Items = std::list<std::string>;
public:
	SceneBase();
	virtual ~SceneBase();
	void _update(float tick);
	void _draw();

	// �V�[������֐�
	template<class T> T* AddSubScene();
	void RemoveSubScene();

	// �I�u�W�F�N�g����֐�
	template<class T> static T* CreateObj(const char* name, eObjectTag tag);
	static void DestroyObj(const char* name);
	template<class T> static T* GetObj(const char* name);
	template<class T> static std::list<T*> GetObjswithTag(eObjectTag tag);

	// �p���V�[���̈�ʂ�̏���
	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update(float tick) = 0;
	virtual void Draw() = 0;

private:
	static Objects m_objects;
	
protected:
	SceneBase* m_pParent;
	SceneBase* m_pSubScene;
	static Items m_items;
};

/// <summary>
/// �T�u�V�[���̒ǉ�
/// </summary>
/// <typeparam name="T">�T�u�V�[���̌^</typeparam>
/// <returns>���������T�u�V�[��</returns>
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
/// �I�u�W�F�N�g�̐���
/// </summary>
/// <typeparam name="T">�I�u�W�F�N�g�̌^</typeparam>
/// <param name="name">�I�u�W�F�N�g�̖���</param>
/// <returns>���������I�u�W�F�N�g</returns>
template<class T> T* SceneBase::CreateObj(const char* name, eObjectTag tag)
{
#ifdef _DEBUG
	// �f�o�b�O���̂݁A���̃_�u�肪�Ȃ����`�F�b�N
	Objects::iterator it = m_objects.find(name);
	if (it != m_objects.end()) {
		static char buf[256];
		sprintf_s(buf, sizeof(buf), "Failed to create object. %s", name);
		MessageBox(NULL, buf, "Error", MB_OK);
		return nullptr;
	}
#endif // _DEBUG

	// �I�u�W�F�N�g����
	std::shared_ptr<T> ptr = std::make_shared<T>();
	m_objects.insert(std::pair<std::string, std::shared_ptr<SceneObjectBase>>(name, std::make_shared<SceneObject<T>>(ptr, tag)));
	m_items.push_back(name);
	return ptr.get();
}

/// <summary>
/// �I�u�W�F�N�g�̎擾
/// </summary>
/// <typeparam name="T">�I�u�W�F�N�g�̌^</typeparam>
/// <param name="name">�I�u�W�F�N�g�̖���</param>
/// <returns>�擾�����I�u�W�F�N�g</returns>
template<class T> T* SceneBase::GetObj(const char* name)
{
    // �I�u�W�F�N�g�̒T��
    Objects::iterator it = m_objects.find(name);
    if (it == m_objects.end()) return nullptr;

    // �^�ϊ�
    std::shared_ptr<SceneObject<T>> ptr = std::reinterpret_pointer_cast<SceneObject<T>>(it->second);
    return ptr->m_pObject.m_pObj.get();
}

template<class T> std::list<T*> SceneBase::GetObjswithTag(eObjectTag tag)
{
	std::list<T*> result;

	for (const auto& pair : m_objects)
	{
		std::shared_ptr<SceneObject<T>> obj = std::dynamic_pointer_cast<SceneObject<T>>(pair.second);
		//const std::type_info& valueType = typeid(pair.second);	//player�Ȃ�
		//bool typeFlag = std::is_base_of<valueType, T>::value;	//ObjectBase�Ȃ�
		//std::shared_ptr<SceneObject<T>> obj = 
		if (obj && obj->m_pObject.m_tag == tag)
		{
			result.push_back(obj->m_pObject.m_pObj.get());
		}
	}

	return result;
}

#endif // __SCENE_BASE_HPP__