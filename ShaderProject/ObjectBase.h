#pragma once
#include "BaseProperty.h"
#include <DirectXMath.h>
#include "Model.h"

class ObjectBase : public BaseProperty
{
public:
	ObjectBase();
	~ObjectBase() {};
	virtual void Update() = 0;
	void Draw();

	void SetPosition(DirectX::XMFLOAT3 pos) { m_Pos = pos; };
	void SetRotation(DirectX::XMFLOAT3 rot) { m_Rot = rot; };
	void SetScale(DirectX::XMFLOAT3 size)   { m_Size = size; };

	DirectX::XMFLOAT3 GetPosition() { return m_Pos; };
	DirectX::XMFLOAT3 GetRotation() { return m_Rot; };
	DirectX::XMFLOAT3 GetScale()    { return m_Size; };

private:
	DirectX::XMFLOAT3 m_Pos;
	DirectX::XMFLOAT3 m_Rot;
	DirectX::XMFLOAT3 m_Size;
	Model* m_pModel;
};

