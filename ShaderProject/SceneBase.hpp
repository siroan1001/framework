#ifndef __SCENE_BASE_HPP__
#define __SCENE_BASE_HPP__

#include <memory>
#include <map>
#include <string>
#include <list>
#include <Windows.h>

// @brief �V�[���ǉ��p�I�u�W�F�N�g
class SceneObjectBase
{
public:
	virtual ~SceneObjectBase() {}
};
template<class T>
class SceneObject : public SceneObjectBase
{
public:
	SceneObject(std::shared_ptr<T> ptr) : m_pObj(ptr) {}
	virtual ~SceneObject() {}
	std::shared_ptr<T> m_pObj;
};

// @breif �V�[����{�N���X
class SceneBase
{
private:
	using Objects = std::map<std::string, std::shared_ptr<SceneObjectBase>>;
	using Items = std::list<std::string >;
public:
	SceneBase();
	virtual ~SceneBase();
	void _update(float tick);
	void _draw();

	// �V�[������֐�
	template<class T> T* AddSubScene();
	void RemoveSubScene();

	// �I�u�W�F�N�g����֐�
	template<class T> T* CreateObj(const char* name);
	void DestroyObj(const char* name);
	template<class T> T* GetObj(const char* name);

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
	Items m_items;
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
template<class T> T* SceneBase::CreateObj(const char* name)
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
	m_objects.insert(std::pair<std::string, std::shared_ptr<SceneObjectBase>>(name, std::make_shared<SceneObject<T>>(ptr)));
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
	return ptr->m_pObj.get();
}

#endif // __SCENE_BASE_HPP__