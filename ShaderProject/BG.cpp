#include "BG.h"
#include "Sprite.h"

void BG::Draw()
{
	if (!m_Use)	return;

	DirectX::XMFLOAT4X4 view;
	XMStoreFloat4x4(&view, DirectX::XMMatrixIdentity());

	DirectX::XMFLOAT4X4 proj;
	XMStoreFloat4x4(&proj, DirectX::XMMatrixTranspose(DirectX::XMMatrixOrthographicOffCenterLH(
		0.0f,		//画面左端の座標
		1280.0f,	//画面右端の座標
		720.0f,		//画面上端の座標
		0.0f,		//画面下端の座標
		-1.0f,		//Z方向で写せる最小値
		1.0f		//Z方向で写せる最大値
	)));

	DirectX::XMMATRIX t = DirectX::XMMatrixTranslation(m_Pos.x, m_Pos.y, 0.0f);
	DirectX::XMFLOAT4X4 world;
	DirectX::XMStoreFloat4x4(&world, XMMatrixTranspose(t));

	Sprite::SetWorld(world);
	Sprite::SetView(view);
	Sprite::SetProjection(proj);
	Sprite::SetSize(m_Size);
	Sprite::SetTexture(m_pTex);
	Sprite::SetColor(m_Color);
	Sprite::SetVertexShader(m_pVS);
	Sprite::SetPixelShader(m_pPS);
	Sprite::SetUVPos(m_uvPos);
	Sprite::SetUVScale(m_uvSize);
	Sprite::Draw();
}
