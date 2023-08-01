#pragma once
#include "BaseProperty.h"
#include <DirectXMath.h>
#include "Model.h"
#include <vector>
#include "ShaderManeger.h"

class ObjectBase : public BaseProperty
{
public:
	struct ShaderPair
	{
		ShaderManeger::VSKind vsKind;
		ShaderManeger::PSKind psKind;
	};

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

protected:
	DirectX::XMFLOAT3 m_Pos;
	DirectX::XMFLOAT3 m_Rot;
	DirectX::XMFLOAT3 m_Size;
	Model* m_pModel;
	std::vector<ShaderPair> m_ShaderPair;
	int m_useShaderPair;
};

