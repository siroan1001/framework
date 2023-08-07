#pragma once

#include "Texture.h"
#include <DirectXMath.h>

class GameUI
{
public:
	GameUI();
	~GameUI();
	void Draw();

private:
	Texture* m_pTex;
	DirectX::XMFLOAT2 m_Pos;
	DirectX::XMFLOAT2 m_Size;
};

