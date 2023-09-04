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

	void SetActive(bool flag) { m_Use = flag; }

	virtual void SetPos(DirectX::XMFLOAT2 pos) { m_Pos = pos; }
	void SetSize(DirectX::XMFLOAT2 size) { m_Size = size; }
	void SetVS(VertexShader* vs) { m_pVS = vs; }
	void SetPS(PixelShader* ps) { m_pPS = ps; }
	void SetUVPos(DirectX::XMFLOAT2 uvpos) { m_uvPos = uvpos; }
	void SetUVSize(DirectX::XMFLOAT2 uvsize) { m_uvSize = uvsize; }
	void SetTexture(Texture* tex) { m_pTex = tex; }

	Texture* GetTex() { return m_pTex; }
	DirectX::XMFLOAT2 GetPos() { return m_Pos; }

	void CreateTex(const char* file)
	{ 
		m_pTex->Create(file);
	}

protected:
	bool m_Use;
	Texture* m_pTex;
	VertexShader* m_pVS;
	PixelShader* m_pPS;
	DirectX::XMFLOAT2 m_Pos;
	DirectX::XMFLOAT2 m_Size;
	float m_Rot;
	DirectX::XMFLOAT2 m_uvPos;
	DirectX::XMFLOAT2 m_uvSize;
};

