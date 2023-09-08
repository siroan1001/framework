#include "Billboard.h"
#include "CameraBase.h"
#include "SceneRoot.h"
#include "Sprite.h"

Billboard::Billboard()
{
	m_pTex = new Texture;
	m_pTex->Create("Assets/Texture/ImageBase.png");
	m_Pos = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	m_Size = DirectX::XMFLOAT2(1.0f, 1.0f);
	//m_Rot = 0.0f;
	m_uvPos = DirectX::XMFLOAT2(0.0f, 0.0f);
	m_uvSize = DirectX::XMFLOAT2(1.0f, 1.0f);
	m_Color = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	m_pVS = nullptr;
	m_pPS = nullptr;
}

Billboard::~Billboard()
{
	if (m_pTex)	delete m_pTex;
}

void Billboard::Draw()
{
	RenderTarget* rtv = SceneBase::GetObj<RenderTarget>("RTV");
	DepthStencil* dsv = SceneBase::GetObj<DepthStencil>("DSV");
	SetRenderTargets(1, &rtv, nullptr);

	CameraBase* cam = SceneRoot::GetCamera();
	Sprite::SetView(cam->GetView());
	Sprite::SetProjection(cam->GetProj());
	DirectX::XMFLOAT4X4 inv;	//�t�s��̊i�[��
	inv = cam->GetView();
	DirectX::XMMATRIX matInv = XMLoadFloat4x4(&inv);
	matInv = XMMatrixTranspose(matInv);	//�]�u����Ă�����̂����ɖ߂����߂ɍēx�]�u����
	//�ړ������͌������K�v���Ȃ��̂łO��ݒ肵�Ĉړ��𖳎�����
	XMStoreFloat4x4(&inv, matInv);
	inv._41 = inv._42 = inv._43 = 0.0f;
	//�t�s��̌v�Z��XMMATRIX�^�ōs��
	matInv = XMLoadFloat4x4(&inv);
	matInv = XMMatrixInverse(nullptr, matInv);
	//�t�s�񁨃��[���h���r���[�̏��Ńr���{�[�h�����

	DirectX::XMFLOAT4X4 world;
	DirectX::XMMATRIX t = DirectX::XMMatrixTranslation(m_Pos.x, m_Pos.y, m_Pos.z);
	XMStoreFloat4x4(&world, XMMatrixTranspose(matInv * t));
	Sprite::SetWorld(world);
	Sprite::SetTexture(m_pTex);
	Sprite::SetSize(m_Size);
	Sprite::SetUVPos(m_uvPos);
	Sprite::SetUVScale(m_uvSize);
	Sprite::SetColor(m_Color);
	Sprite::SetVertexShader(m_pVS);
	Sprite::SetPixelShader(m_pPS);

	Sprite::Draw();

	SetRenderTargets(1, &rtv, dsv);
}