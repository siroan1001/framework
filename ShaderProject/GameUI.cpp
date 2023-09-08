#include "GameUI.h"
#include "Sprite.h"
#include "SceneBase.hpp"

GameUI::GameUI() : m_Use(true), m_pVS(nullptr), m_pPS(nullptr)
{
	m_pTex = new Texture;
	m_pTex->Create("Assets/Texture/ImageBase.png");
	m_Pos = { 0.0f, 0.0f };
	m_Size = { 300.0f, 300.0f };
	m_Rot = 0.0f;
	m_Color = { 1.0f, 1.0f, 1.0f, 1.0f };
	m_uvPos = { 0.0f, 0.0f };
	m_uvSize = { 1.0f, -1.0f };
}

GameUI::~GameUI()
{
	if (m_pTex)	delete m_pTex;
}

void GameUI::Draw()
{
	if (!m_Use)	return;

	RenderTarget* rtv = SceneBase::GetObj<RenderTarget>("RTV");
	DepthStencil* dsv = SceneBase::GetObj<DepthStencil>("DSV");
	SetRenderTargets(1, &rtv, nullptr);

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
	)
	));

	DirectX::XMMATRIX t = DirectX::XMMatrixTranslation(m_Pos.x, m_Pos.y, 0.0f);
	DirectX::XMMATRIX r = DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(m_Rot));
	DirectX::XMFLOAT4X4 world;
	DirectX::XMStoreFloat4x4(&world, XMMatrixTranspose(r * t));
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

	SetRenderTargets(1, &rtv, dsv);
}