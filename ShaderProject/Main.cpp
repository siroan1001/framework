#include "Main.h"
#include <memory>
#include "DirectX.h"
#include "Geometory.h"
#include "Sprite.h"
#include "Input.h"
#include "SceneRoot.h"

//--- �O���[�o���ϐ�
std::shared_ptr<SceneRoot> g_pScene;

HRESULT Init(HWND hWnd, UINT width, UINT height)
{
	HRESULT hr;
	hr = InitDirectX(hWnd, width, height, false);
	if (FAILED(hr)) { return hr; }
	Geometory::Init();
	Sprite::Init();
	InitInput();

	// �V�[���쐬
	g_pScene = std::make_shared<SceneRoot>();
	g_pScene->Init();

	// �������\�[�X�쐬
	auto rtv = g_pScene->CreateObj<RenderTarget>("RTV", eObjectTag::E_OBJ_TAG_RTV);
	rtv->CreateFromScreen();
	auto dsv = g_pScene->CreateObj<DepthStencil>("DSV", eObjectTag::E_OBJ_TAG_DSV);
	hr = dsv->Create(width, height, false);

	SetRenderTargets(1, &rtv, dsv);

	return hr;
}

void Uninit()
{
	g_pScene->Uninit();
	g_pScene.reset();
	UninitInput();
	Sprite::Uninit();
	Geometory::Uninit();
	UninitDirectX();
}

void Update(float tick)
{
	UpdateInput();
	g_pScene->_update(tick);
}

void Draw()
{
	auto rtv = g_pScene->GetObj<RenderTarget>("RTV");
	auto dsv = g_pScene->GetObj<DepthStencil>("DSV");
	float color[4] = { 0.8f, 0.9f, 1.0f, 1.0f };
	GetContext()->ClearRenderTargetView(rtv->GetView(), color);
	GetContext()->ClearDepthStencilView(dsv->GetView(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	g_pScene->_draw();
	
	SwapDirectX();
}

// EOF