#pragma once



class Component
{

protected:

	class  GameObject* m_GameObject = nullptr;

public:
	Component() = delete;	// �f�t�H���g�R���X�g���N�^����
	Component(GameObject* Object) { m_GameObject = Object; }
	virtual ~Component() {}

	virtual void Init() {};
	virtual void Uninit() {};
	virtual void Update() {};
	virtual void Draw() {};



};
