#include "SceneGame.h"
#include "Model.h"
#include "CameraBase.h"
#include "LightBase.h"
#include "Input.h"

#include "Player.h"

void SceneGame::Init()
{
	Shader* shader[] = {
		CreateObj<VertexShader>("VS_Object", eObjectTag::E_OBJ_TAG_SHEDER),
		//CreateObj<VertexShader>("VS_GouraudShading"),
		CreateObj<PixelShader>("PS_TexColor", eObjectTag::E_OBJ_TAG_SHEDER),
		//CreateObj<PixelShader>("PS_PhongShading"),
		//CreateObj<PixelShader>("PS_GouraudShading"),
		//CreateObj<PixelShader>("PS_Specular"),
		//CreateObj<VertexShader>("VS_WorldPosition"),
		//CreateObj<PixelShader>("PS_LimLight")
	};
	const char* file[] = {
		"Assets/Shader/VS_Object.cso",
		//"Assets/Shader/VS_GouraudShading.cso",
		"Assets/Shader/PS_TexColor.cso",
		//"Assets/Shader/PS_PhongShading.cso",
		//"Assets/Shader/PS_GouraudShading.cso",
		//"Assets/Shader/PS_Specular.cso",
		//"Assets/Shader/VS_WorldPosition.cso",
		//"Assets/Shader/PS_LimLight.cso"
	};

	int shaderNum = _countof(shader);
	for (int i = 0; i < shaderNum; ++i)
	{
		if (FAILED(shader[i]->Load(file[i])))
		{
			MessageBox(NULL, file[i], "Shader Error", MB_OK);
		}
	}

	Player* modelA = CreateObj<Player>("ModelA", eObjectTag::E_OBJ_TAG_OBJ);
	Player* modelB = CreateObj<Player>("ModelB", eObjectTag::E_OBJ_TAG_OBJ);
	Player* modelC = CreateObj<Player>("ModelC", eObjectTag::E_OBJ_TAG_OBJ);
	
}
void SceneGame::Uninit()
{
}
void SceneGame::Update(float tick)
{
}

void SceneGame::Draw()
{
	////	Rootクラスで読み込みされているModelを取得
	////	GetObj　引数で指定された名前のデータを
	////			テンプレート引数に指定された型に変換して取得
	////Model* pModel = GetObj<Model>("Model");
	//CameraBase* pCamera = GetObj<CameraBase>("Camera");
	//LightBase* pLight = GetObj<LightBase>("Light");

	////	定数バッファで渡す行列の情報
	//DirectX::XMFLOAT4X4 mat[3];
	//DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixIdentity());
	//mat[1] = pCamera->GetView();
	//mat[2] = pCamera->GetProj();
	////	定数バッファに渡すライトの情報
	//DirectX::XMFLOAT3 lightDir =
	//	pLight->GetDirection();
	//DirectX::XMFLOAT4 light[] = {
	//	pLight->GetDiffuse(),
	//	pLight->GetAmbient(),
	//	{lightDir.x, lightDir.y, lightDir.z, 0.0f}
	//};

	////	定数バッファに渡すカメラの情報
	//DirectX::XMFLOAT3 camPos = pCamera->GetPos();
	//DirectX::XMFLOAT4 camera[] = {
	//	{camPos.x, camPos.y, camPos.z, 0.0f}
	//};

	////	シェーダーの取得
	//Shader* shader[] = {
	//	GetObj<Shader>("VS_Object"),
	//	//GetObj<Shader>("VS_GouraudShading"),
	//	GetObj<Shader>("PS_TexColor"),
	//	//GetObj<Shader>("PS_PhongShading"),
	//	//GetObj<Shader>("PS_GouraudShading"),
	//	//GetObj<Shader>("PS_Specular"),
	//	//GetObj<Shader>("VS_WorldPosition"),
	//	//GetObj<Shader>("PS_LimLight")
	//};
	//int shaderPair[][2] = {
	//	{0, 1}, //	通常表示
	//	//{0, 3},	//	フォンシェーディング
	//	//{1, 4},	//	グローシェーディング
	//	//{6, 5},	//	鏡面反射
	//	//{6, 7},	//	リムライト
	//};

	std::list<ObjectBase*> objlist = GetObjswithTag<ObjectBase>(eObjectTag::E_OBJ_TAG_OBJ);

	for (ObjectBase* obj : objlist)
	{
		obj->Draw();
	}

	//	描画
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