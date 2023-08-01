#include "ObjectBase.h"
#include "Model.h"
#include "CameraBase.h"
#include "LightBase.h"
#include "SceneBase.hpp"
#include "Shader.h"
#include "ShaderManeger.h"

ObjectBase::ObjectBase() : 
	m_Pos(0.0f, 0.0f, 0.0f),
	m_Rot(0.0f, 0.0f, 0.0f),
	m_Size(1.0f, 1.0f, 1.0f),
	m_useShaderPair(0)
{
	m_pModel = new Model();
	m_pModel->Load("Assets/Model/spot/spot.fbx", 1.0f, true);

	ShaderPair pair = { ShaderManeger::VSKind::E_VS_OBJECT, ShaderManeger::PSKind::E_PS_TEXCOLOR };
	m_ShaderPair.push_back(pair);
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
	Shader* shader[] = {
		SceneBase::GetObj<Shader>("VS_Object"),
		SceneBase::GetObj<Shader>("PS_TexColor"),
	};
	int shaderPair[][2] = {
		{0, 1}, //	通常表示
	};

	VertexShader* VS = ShaderManeger::GetVSShader(m_ShaderPair[m_useShaderPair].vsKind);
	PixelShader* PS = ShaderManeger::GetPSShader(m_ShaderPair[m_useShaderPair].psKind);

	//　描画
	//	座標の更新
	DirectX::XMStoreFloat4x4(&mat[0],
		DirectX::XMMatrixTranspose(
			DirectX::XMMatrixTranslation(m_Pos.x, m_Pos.y, m_Pos.z)));

	//	定数バッファの更新
	VS->WriteBuffer(0, mat);
	VS->WriteBuffer(1, light);
	PS->WriteBuffer(0, light);
	PS->WriteBuffer(0, camera);

	//	描画
	m_pModel->SetVertexShader(VS);
	m_pModel->SetPixelShader(PS);
	m_pModel->Draw();


}
