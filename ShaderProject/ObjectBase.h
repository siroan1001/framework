#pragma once
#include "BaseProperty.h"
#include <DirectXMath.h>
#include "Model.h"
#include <vector>
#include "ShaderManager.h"

class ObjectBase : public BaseProperty
{
public:
	struct ShaderPair
	{
		ShaderManager::VSKind vsKind;
		ShaderManager::PSKind psKind;
		ShaderManager::VS_BUF vsBuf;
		ShaderManager::PS_BUF psBuf;
	};

public:
	ObjectBase();
	~ObjectBase();
	virtual void Update() = 0;
	void Draw();

	void WriteShaderBuffer(VertexShader* VS, PixelShader* PS);

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
	std::shared_ptr<Model> m_pModel;
	ShaderPair m_ShaderPair;
	bool m_Use;
};

