#include "GameUI.h"
#include "Sprite.h"

GameUI::GameUI()
{
	m_pTex = new Texture;
	m_pTex->Create("Assets/Texture/space.png");

	m_Pos = { 0.0f, 0.0f };
	m_Size = { 300.0f, 300.0f };
}

GameUI::~GameUI()
{
	if (m_pTex)	delete m_pTex;
}

void GameUI::Draw()
{
	DirectX::XMFLOAT4X4 view;
	XMStoreFloat4x4(&view, DirectX::XMMatrixIdentity());

	DirectX::XMFLOAT4X4 proj;
	XMStoreFloat4x4(&proj, DirectX::XMMatrixTranspose(DirectX::XMMatrixOrthographicOffCenterLH(
		0.0f,		//��ʍ��[�̍��W
		1280.0f,	//��ʉE�[�̍��W
		720.0f,		//��ʏ�[�̍��W
		0.0f,		//��ʉ��[�̍��W
		-1.0f,		//Z�����Ŏʂ���ŏ��l
		1.0f		//Z�����Ŏʂ���ő�l
	)
	));

	DirectX::XMMATRIX t = DirectX::XMMatrixTranslation(m_Pos.x, m_Pos.y, 0.0f);
	DirectX::XMFLOAT4X4 world;
	DirectX::XMStoreFloat4x4(&world, XMMatrixTranspose(t));

	Sprite::SetWorld(world);
	Sprite::SetView(view);
	Sprite::SetProjection(proj);
	Sprite::SetSize(m_Size);
	Sprite::SetTexture(m_pTex);
	Sprite::Draw();
}
