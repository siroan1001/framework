#include "ObjectBase.h"
#include "Model.h"
#include "CameraBase.h"
#include "LightBase.h"
#include "SceneBase.hpp"
#include "Shader.h"

void ObjectBase::Draw()
{
	//	Root�N���X�œǂݍ��݂���Ă���Model���擾
//	GetObj�@�����Ŏw�肳�ꂽ���O�̃f�[�^��
//			�e���v���[�g�����Ɏw�肳�ꂽ�^�ɕϊ����Ď擾
//Model* pModel = GetObj<Model>("Model");
	CameraBase* pCamera = SceneBase::GetObj<CameraBase>("Camera");
	LightBase* pLight = SceneBase::GetObj<LightBase>("Light");

	//	�萔�o�b�t�@�œn���s��̏��
	DirectX::XMFLOAT4X4 mat[3];
	DirectX::XMStoreFloat4x4(&mat[0], DirectX::XMMatrixIdentity());
	mat[1] = pCamera->GetView();
	mat[2] = pCamera->GetProj();
	//	�萔�o�b�t�@�ɓn�����C�g�̏��
	DirectX::XMFLOAT3 lightDir =
		pLight->GetDirection();
	DirectX::XMFLOAT4 light[] = {
		pLight->GetDiffuse(),
		pLight->GetAmbient(),
		{lightDir.x, lightDir.y, lightDir.z, 0.0f}
	};

	//	�萔�o�b�t�@�ɓn���J�����̏��
	DirectX::XMFLOAT3 camPos = pCamera->GetPos();
	DirectX::XMFLOAT4 camera[] = {
		{camPos.x, camPos.y, camPos.z, 0.0f}
	};

	//	�V�F�[�_�[�̎擾
	Shader* shader[] = {
		SceneBase::GetObj<Shader>("VS_Object"),
		SceneBase::GetObj<Shader>("PS_TexColor"),
	};
	int shaderPair[][2] = {
		{0, 1}, //	�ʏ�\��
	};

	////	�`��
	//int drawNum = _countof(shaderPair);
	//for (int i = 0; i < drawNum; ++i)
	//{
	//	//	���W�̍X�V
	//	DirectX::XMStoreFloat4x4(&mat[0],
	//		DirectX::XMMatrixTranspose(
	//			DirectX::XMMatrixTranslation(
	//				(drawNum - 1) * 0.5f - i, 0.0f, 0.0f
	//			)));

	//	//	�萔�o�b�t�@�̍X�V
	//	shader[shaderPair[i][0]]->WriteBuffer(0, mat);
	//	shader[shaderPair[i][0]]->WriteBuffer(1, light);
	//	shader[shaderPair[i][1]]->WriteBuffer(0, light);
	//	shader[shaderPair[i][1]]->WriteBuffer(0, camera);

	//	//	�`��
	//	pModel->SetVertexShader(shader[shaderPair[i][0]]);
	//	pModel->SetPixelShader(shader[shaderPair[i][1]]);
	//	pModel->Draw();
	//}

}
