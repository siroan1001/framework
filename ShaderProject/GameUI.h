#pragma once

#include "Texture.h"
#include "Shader.h"
#include <DirectXMath.h>

class GameUI
{
public:
	GameUI();
	~GameUI();
	virtual void Draw();

	virtual void SetPos(DirectX::XMFLOAT2 pos) { m_Pos = pos; }
	void SetSize(DirectX::XMFLOAT2 size) { m_Size = size; }
	void SetVS(VertexShader* vs) { m_pVS = vs; }
	void SetPS(PixelShader* ps) { m_pPS = ps; }

	Texture* GetTex() { return m_pTex; }

	void CreateTex(const char* file) { m_pTex->Create(file); }

protected:
	Texture* m_pTex;
	VertexShader* m_pVS;
	PixelShader* m_pPS;
	DirectX::XMFLOAT2 m_Pos;
	DirectX::XMFLOAT2 m_Size;
};

