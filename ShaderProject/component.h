#pragma once



class Component
{

protected:

	class  GameObject* m_GameObject = nullptr;

public:
	Component() = delete;	// デフォルトコンストラクタ無し
	Component(GameObject* Object) { m_GameObject = Object; }
	virtual ~Component() {}

	virtual void Init() {};
	virtual void Uninit() {};
	virtual void Update() {};
	virtual void Draw() {};



};
