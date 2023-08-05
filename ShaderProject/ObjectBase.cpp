#include "ObjectBase.h"
#include "Model.h"
#include "CameraBase.h"
#include "LightBase.h"
#include "SceneBase.hpp"
#include "Shader.h"
#include "ShaderManager.h"

ObjectBase::ObjectBase() : 
	m_Pos(0.0f, 0.0f, 0.0f),
	m_Rot(0.0f, 0.0f, 0.0f),
	m_Size(1.0f, 1.0f, 1.0f)
{
	m_ShaderPair.vsKind = ShaderManager::VSKind::E_VS_OBJECT;
	m_ShaderPair.psKind = ShaderManager::PSKind::E_PS_GOURAUDSHADING;
}

ObjectBase::~ObjectBase()
{
}

void ObjectBase::Draw()
{
	CameraBase* pCamera = SceneBase::GetCamera();
	LightBase*  pLight  = SceneBase::GetObj<LightBase>("Light");

	//	定数バッファで渡す行列の情報
	DirectX::XMFLOAT4X4 mat[3];
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixIdentity());
	mat[1] = pCamera->GetView();
	mat[2] = pCamera->GetProj();

	//	定数バッファに渡すライトの情報
	DirectX::XMFLOAT3 lightDir = pLight->GetDirection();
	DirectX::XMFLOAT4 light[] = {
		pLight->GetDiffuse(),
		pLight->GetAmbient(),
		{lightDir.x, lightDir.y, lightDir.z, 0.0f}
	};

	//	定数バッファに渡すカメラの情報
	DirectX::XMFLOAT3 camPos = pCamera->GetPos();
	DirectX::XMFLOAT4 camera[] = { {camPos.x, camPos.y, camPos.z, 0.0f} };

	//	シェーダーの取得
	VertexShader* VS = ShaderManager::GetVSShader(m_ShaderPair.vsKind);
	PixelShader* PS = ShaderManager::GetPSShader(m_ShaderPair.psKind);

	//　描画
	//	座標の更新
	DirectX::XMStoreFloat4x4(&mat[0],
		DirectX::XMMatrixTranspose(
			DirectX::XMMatrixTranslation(m_Pos.x, m_Pos.y, m_Pos.z)));

	if (m_ShaderPair.vsKind == ShaderManager::VSKind::E_VS_OBJECT)
	{
		m_ShaderPair.vsBuf.Buf.ObjectBuf.world = mat[0];
		m_ShaderPair.vsBuf.Buf.ObjectBuf.view = mat[1];
		m_ShaderPair.vsBuf.Buf.ObjectBuf.proj = mat[2];
	}

	//	定数バッファ設定
	WriteShaderBuffer(VS, PS);

	//	描画
	m_pModel->SetVertexShader(VS);
	m_pModel->SetPixelShader(PS);
	m_pModel->Draw();
}

void ObjectBase::WriteShaderBuffer(VertexShader* VS, PixelShader* PS)
{
	switch (m_ShaderPair.vsKind)
	{
	case ShaderManager::VSKind::E_VS_OBJECT:
		VS->WriteBuffer(0, &m_ShaderPair.vsBuf.Buf.ObjectBuf);
		break;
	default:
		break;
	}

	switch (m_ShaderPair.psKind)
	{
	default:
		break;
	}
}
