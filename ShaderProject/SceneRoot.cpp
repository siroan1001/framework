#include "SceneRoot.h"
#include <stdio.h>
#include "CameraDCC.h"
#include "MoveLight.h"
#include "Model.h"
#include "Input.h"
#include "Geometory.h"

#include "SceneGame.h"

//--- �萔��`
enum SceneKind
{
	SCENE_GAME,
	SCENE_MAX
};

void SceneRoot::ChangeScene()
{
	switch (m_index)
	{
	default:
	case SCENE_GAME: AddSubScene<SceneGame>();
	}
}


//--- �\����
// @brief �V�[�����ۑ�
struct ViewSetting
{
	DirectX::XMFLOAT3 camPos;
	DirectX::XMFLOAT3 camLook;
	DirectX::XMFLOAT3 camUp;
	float lightRadXZ;
	float lightRadY;
	float lightH;
	float lightSV;
	int index;
};
const char* SettingFileName = "Assets/setting.dat";

void SceneRoot::Init()
{
	// �ۑ��f�[�^�̓ǂݍ���
	ViewSetting setting =
	{
		DirectX::XMFLOAT3(0.0f, 1.0f, -5.0f),
		DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f),
		DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f),
		0.0f, DirectX::XM_PIDIV4,
		0.0f, 1.0f,
		SCENE_GAME
	};

	//�S�V�[���ŋ��ʂ��Ďg�����̂��쐬

	// ���C�g�̍쐬
	MoveLight* pLight = CreateObj<MoveLight>("Light", eObjectTag::E_OBJ_TAG_LIGHT);
	pLight->SetRot(setting.lightRadXZ, setting.lightRadY);
	pLight->SetHSV(setting.lightH, setting.lightSV);
	pLight->UpdateParam();

	ShaderManeger& ShaderMane = ShaderManeger::GetInstance();

	// �V�[���̍쐬
	m_index = setting.index;
	ChangeScene();
}

void SceneRoot::Uninit()
{
	//CameraBase* pCamera = GetObj<CameraBase>("Camera");
	//MoveLight* pLight = GetObj<MoveLight>("Light");
	//ViewSetting setting =
	//{
	//	pCamera->GetPos(),
	//	pCamera->GetLook(),
	//	pCamera->GetUp(),
	//	pLight->GetRotXZ(), pLight->GetRotY(),
	//	pLight->GetH(), pLight->GetSV(),
	//	m_index
	//};
	//FILE* fp;
	//fopen_s(&fp, SettingFileName, "wb");
	//if (fp)
	//{
	//	fwrite(&setting, sizeof(ViewSetting), 1, fp);
	//	fclose(fp);
	//}
}

void SceneRoot::Update(float tick)
{
	CameraBase* pCamera = GetObj<CameraBase>("Camera");
	LightBase* pLight = GetObj<LightBase>("Light");

	//// SHIFT�L�[��������Ă�΁A�V�[���̐؂�ւ�����
	int idx = m_index;

	if (idx != m_index)
	{
		m_index = idx;
		RemoveSubScene();
		ChangeScene();
	}

	// �J����������
	if (IsKeyTrigger('R'))
	{
		pCamera->SetPos(DirectX::XMFLOAT3(0.0f, 1.0f, -5.0f));
		pCamera->SetLook(DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f));
		pCamera->SetUp(DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f));
	}
}
void SceneRoot::Draw()
{
	CameraBase* pCamera = GetCamera();
	LightBase* pLight = GetObj<LightBase>("Light");

	DirectX::XMFLOAT4X4 fmat;
	DirectX::XMStoreFloat4x4(&fmat, DirectX::XMMatrixIdentity());
	Geometory::SetWorld(fmat);
	Geometory::SetView(pCamera->GetView());
	Geometory::SetProjection(pCamera->GetProj());

	// �Ԋ|���`��
	const int GridSize = 10;
	Geometory::SetColor(DirectX::XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f));
	for (int i = 1; i <= GridSize; ++i)
	{
		float g = (float)i;
		Geometory::AddLine(DirectX::XMFLOAT3(g, 0.0f, -GridSize), DirectX::XMFLOAT3(g, 0.0f, GridSize));
		Geometory::AddLine(DirectX::XMFLOAT3(-g, 0.0f, -GridSize), DirectX::XMFLOAT3(-g, 0.0f, GridSize));
		Geometory::AddLine(DirectX::XMFLOAT3(-GridSize, 0.0f, g), DirectX::XMFLOAT3(GridSize, 0.0f, g));
		Geometory::AddLine(DirectX::XMFLOAT3(-GridSize, 0.0f, -g), DirectX::XMFLOAT3(GridSize, 0.0f, -g));
	}
	// ���`��
	Geometory::SetColor(DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));
	Geometory::AddLine(DirectX::XMFLOAT3(-GridSize, 0.0f, 0.0f), DirectX::XMFLOAT3(GridSize, 0.0f, 0.0f));
	Geometory::SetColor(DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
	Geometory::AddLine(DirectX::XMFLOAT3(0.0f, -GridSize, 0.0f), DirectX::XMFLOAT3(0.0f, GridSize, 0.0f));
	Geometory::SetColor(DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f));
	Geometory::AddLine(DirectX::XMFLOAT3(0.0f, 0.0f, -GridSize), DirectX::XMFLOAT3(0.0f, 0.0f, GridSize));

	Geometory::DrawLines();

	// �I�u�W�F�N�g�`��
	pCamera->Draw();
	pLight->Draw();
}
