#pragma once
#include "Texture.h"
#include <DirectXMath.h>
#include "Shader.h"

class Billboard
{
public:
	Billboard();
	~Billboard();
	void Draw();

	void CreateTex(const char* file) { m_pTex->Create(file); }
	void SetPos(DirectX::XMFLOAT3 pos) { m_Pos = pos; }
	void SetSize(DirectX::XMFLOAT2 size) { m_Size = size; }

private:
	Texture* m_pTex;
	DirectX::XMFLOAT3 m_Pos;
	DirectX::XMFLOAT2 m_Size;
	//float m_Rot;
	DirectX::XMFLOAT2 m_uvPos;
	DirectX::XMFLOAT2 m_uvSize;
	DirectX::XMFLOAT4 m_Color;
	VertexShader* m_pVS;
	PixelShader* m_pPS;
};

