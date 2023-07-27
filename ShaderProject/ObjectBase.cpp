#include "ObjectBase.h"
#include "Model.h"
#include "CameraBase.h"
#include "LightBase.h"
#include "SceneBase.hpp"
#include "Shader.h"

void ObjectBase::Draw()
{
	//	Rootクラスで読み込みされているModelを取得
//	GetObj　引数で指定された名前のデータを
//			テンプレート引数に指定された型に変換して取得
//Model* pModel = GetObj<Model>("Model");
	CameraBase* pCamera = SceneBase::GetObj<CameraBase>("Camera");
	LightBase* pLight = SceneBase::GetObj<LightBase>("Light");

	//	定数バッファで渡す行列の情報
	DirectX::XMFLOAT4X4 mat[3];
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixIdentity());
	mat[1] = pCamera->GetView();
	mat[2] = pCamera->GetProj();
	//	定数バッファに渡すライトの情報
	DirectX::XMFLOAT3 lightDir =
		pLight->GetDirection();
	DirectX::XMFLOAT4 light[] = {
		pLight->GetDiffuse(),
		pLight->GetAmbient(),
		{lightDir.x, lightDir.y, lightDir.z, 0.0f}
	};

	//	定数バッファに渡すカメラの情報
	DirectX::XMFLOAT3 camPos = pCamera->GetPos();
	DirectX::XMFLOAT4 camera[] = {
		{camPos.x, camPos.y, camPos.z, 0.0f}
	};

	//	シェーダーの取得
	Shader* shader[] = {
		SceneBase::GetObj<Shader>("VS_Object"),
		SceneBase::GetObj<Shader>("PS_TexColor"),
	};
	int shaderPair[][2] = {
		{0, 1}, //	通常表示
	};

	////	描画
	//int drawNum = _countof(shaderPair);
	//for (int i = 0; i < drawNum; ++i)
	//{
	//	//	座標の更新
	//	DirectX::XMStoreFloat4x4(&mat[0],
	//		DirectX::XMMatrixTranspose(
	//			DirectX::XMMatrixTranslation(
	//				(drawNum - 1) * 0.5f - i, 0.0f, 0.0f
	//			)));

	//	//	定数バッファの更新
	//	shader[shaderPair[i][0]]->WriteBuffer(0, mat);
	//	shader[shaderPair[i][0]]->WriteBuffer(1, light);
	//	shader[shaderPair[i][1]]->WriteBuffer(0, light);
	//	shader[shaderPair[i][1]]->WriteBuffer(0, camera);

	//	//	描画
	//	pModel->SetVertexShader(shader[shaderPair[i][0]]);
	//	pModel->SetPixelShader(shader[shaderPair[i][1]]);
	//	pModel->Draw();
	//}

}
