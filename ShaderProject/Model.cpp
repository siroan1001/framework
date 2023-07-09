#include "Model.h"
#include "Defines.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#if _MSC_VER >= 1920
#ifdef _DEBUG
#pragma comment(lib, "assimp/x64/Debug/assimp-vc142-mtd.lib")
#else
#pragma comment(lib, "assimp/x64/Release/assimp-vc142-mt.lib")
#endif
#elif _MSC_VER >= 1910
#ifdef _DEBUG
#pragma comment(lib, "assimp/x64/Debug/assimp-vc141-mtd.lib")
#endif
#endif

std::shared_ptr<VertexShader> Model::m_defVS = nullptr;
std::shared_ptr<PixelShader> Model::m_defPS = nullptr;

Model::Model()
	: m_pVS(nullptr)
	, m_pPS(nullptr)
{
	if (!m_defVS && !m_defPS) // �ǂ����nullptr
	{
		MakeDefaultShader();
	}
	m_pVS = m_defVS.get();
	m_pPS = m_defPS.get();
}
Model::~Model()
{
}

void Model::SetVertexShader(Shader* vs)
{
	VertexShader* cast = reinterpret_cast<VertexShader*>(vs);
	if(cast)
		m_pVS = cast;
}
void Model::SetPixelShader(Shader* ps)
{
	PixelShader* cast = reinterpret_cast<PixelShader*>(ps);
	if (cast)
		m_pPS = cast;
}

const Model::Mesh* Model::GetMesh(unsigned int index)
{
	if (index < 0 || m_meshes.size() <= index)
	{
		return nullptr;
	}
	return &m_meshes[index];
}

uint32_t Model::GetMeshNum()
{
	return static_cast<uint32_t>(m_meshes.size()) ;
}

bool Model::Load(const char* file, float scale, bool flip)
{
	// assimp�̐ݒ�
	Assimp::Importer importer;
	int flag = 0;
	flag |= aiProcess_Triangulate;
	flag |= aiProcess_JoinIdenticalVertices;
	flag |= aiProcess_FlipUVs;
	flag |= aiProcess_PreTransformVertices;
	if (flip) flag |= aiProcess_MakeLeftHanded;
	// assimp�œǂݍ���
	const aiScene* pScene = importer.ReadFile(file, flag);
	if (!pScene) {
		Error(importer.GetErrorString());
		return false;
	}

	// ���b�V���̍쐬
	aiVector3D zero(0.0f, 0.0f, 0.0f);
	for (unsigned int i = 0; i < pScene->mNumMeshes; ++i)
	{
		Mesh mesh = {};

		// ���_�̍쐬
		std::vector<Vertex> vtx;
		vtx.resize(pScene->mMeshes[i]->mNumVertices);
		for (unsigned int j = 0; j < vtx.size(); ++j)
		{
			// �l�̋z�o��
			aiVector3D pos = pScene->mMeshes[i]->mVertices[j];
			aiVector3D uv = pScene->mMeshes[i]->HasTextureCoords(0) ?
				pScene->mMeshes[i]->mTextureCoords[0][j] : zero;
			aiVector3D normal = pScene->mMeshes[i]->HasNormals() ?
				pScene->mMeshes[i]->mNormals[j] : zero;
			// �l��ݒ�
			vtx[j] = {
				DirectX::XMFLOAT3(pos.x * scale, pos.y * scale, pos.z * scale),
				DirectX::XMFLOAT3(normal.x, normal.y, normal.z),
				DirectX::XMFLOAT2(uv.x, uv.y),
			};
		}

		// �C���f�b�N�X�̍쐬
		std::vector<unsigned int> idx;
		idx.resize(pScene->mMeshes[i]->mNumFaces * 3); // face�̓|���S���̐���\��(�P�|���S����3�C���f�b�N�X
		for (unsigned int j = 0; j < pScene->mMeshes[i]->mNumFaces; ++j)
		{
			aiFace face = pScene->mMeshes[i]->mFaces[j];
			int faceIdx = j * 3;
			idx[faceIdx + 0] = face.mIndices[0];
			idx[faceIdx + 1] = face.mIndices[1];
			idx[faceIdx + 2] = face.mIndices[2];
		}

		// �}�e���A���̊��蓖��
		mesh.materialID = pScene->mMeshes[i]->mMaterialIndex;

		// ���b�V�������ɒ��_�o�b�t�@�쐬
		MeshBuffer::Description desc = {};
		desc.pVtx = vtx.data();
		desc.vtxSize = sizeof(Vertex);
		desc.vtxCount = static_cast<UINT>(vtx.size());
		desc.pIdx = idx.data();
		desc.idxSize = sizeof(unsigned int);
		desc.idxCount = static_cast<UINT>(idx.size());
		desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		mesh.mesh = std::make_shared<MeshBuffer>(desc);

		// ���b�V���ǉ�
		m_meshes.push_back(mesh);
	}

	//--- �}�e���A���̍쐬
	// �t�@�C���̒T��
	std::string dir = file;
	dir = dir.substr(0, dir.find_last_of('/') + 1);
	// �}�e���A��
	aiColor3D color(0.0f, 0.0f, 0.0f);
	DirectX::XMFLOAT4 diffuse(1.0f, 1.0f, 1.0f, 1.0f);
	DirectX::XMFLOAT4 ambient(0.3f, 0.3f, 0.3f, 1.0f);
	for (unsigned int i = 0; i < pScene->mNumMaterials; ++i)
	{
		Material material = {};

		// �e��p�����[�^�[
		float shininess;
		material.diffuse = pScene->mMaterials[i]->Get(AI_MATKEY_COLOR_DIFFUSE, color) == AI_SUCCESS ?
			DirectX::XMFLOAT4(color.r, color.g, color.b, 1.0f) : diffuse;
		material.ambient = pScene->mMaterials[i]->Get(AI_MATKEY_COLOR_AMBIENT, color) == AI_SUCCESS ?
			DirectX::XMFLOAT4(color.r, color.g, color.b, 1.0f) : ambient;
		shininess = pScene->mMaterials[i]->Get(AI_MATKEY_SHININESS, shininess) == AI_SUCCESS ? shininess : 0.0f;
		material.specular = pScene->mMaterials[i]->Get(AI_MATKEY_COLOR_SPECULAR, color) == AI_SUCCESS ?
			DirectX::XMFLOAT4(color.r, color.g, color.b, shininess) : DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, shininess);

		// �e�N�X�`��
		HRESULT hr;
		aiString path;
		if (pScene->mMaterials[i]->Get(AI_MATKEY_TEXTURE_DIFFUSE(0), path) == AI_SUCCESS) {
			// ���̂܂ܒT��
			material.texture = std::make_shared<Texture>();
			hr = material.texture->Create(path.C_Str());
			// ���f���Ɠ����K�w��T��
			if (FAILED(hr)) {
				std::string file = dir;
				file += path.C_Str();
				hr = material.texture->Create(file.c_str());
			}
			// �t�@�C�����݂̂ŒT��
			if (FAILED(hr)) {
				std::string file = path.C_Str();
				size_t idx = file.find_last_of('\\');
				if (idx != std::string::npos)
				{
					file = file.substr(idx + 1);
					file = dir + file;
					hr = material.texture->Create(file.c_str());
				}
			}
			// ���s
			if (FAILED(hr)) {
				Error(path.C_Str());
				material.texture = nullptr;
			}
		}
		else {
			material.texture = nullptr;
		}

		// �}�e���A���ǉ�
		m_materials.push_back(material);
	}

	return true;
}

void Model::Draw(int texSlot)
{
	m_pVS->Bind();
	m_pPS->Bind();
	auto it = m_meshes.begin();
	while (it != m_meshes.end())
	{
		if(texSlot >= 0)
			m_pPS->SetTexture(texSlot, m_materials[it->materialID].texture.get());
		it->mesh->Draw();
		++it;
	}
}

void Model::RemakeVertex(int vtxSize, std::function<void(RemakeInfo& data)> func)
{
	auto it = m_meshes.begin();
	while (it != m_meshes.end())
	{
		MeshBuffer::Description desc = it->mesh->GetDesc();
		
		char* newVtx = new char[vtxSize * desc.vtxCount];
		RemakeInfo data = {};
		data.vtxNum = desc.vtxCount;
		data.dest = newVtx;
		data.source = desc.pVtx;
		data.idxNum = desc.idxCount;
		data.idx = desc.pIdx;
		func(data);

		desc.pVtx = newVtx;
		desc.vtxSize = vtxSize;
		it->mesh = std::make_shared<MeshBuffer>(desc);

		delete[] newVtx;
		++it;
	}
}

void Model::MakeDefaultShader()
{
	const char* vsCode = R"EOT(
struct VS_IN {
	float3 pos : POSITION0;
	float3 normal : NORMAL0;
	float2 uv : TEXCOORD0;
};
struct VS_OUT {
	float4 pos : SV_POSITION;
};
VS_OUT main(VS_IN vin) {
	VS_OUT vout;
	vout.pos = float4(vin.pos, 1.0f);
	vout.pos.z *= 0.1f;
	return vout;
})EOT";
	const char* psCode = R"EOT(
struct PS_IN {
	float4 pos : SV_POSITION;
};
float4 main(PS_IN pin) : SV_TARGET
{
	return float4(1.0f, 0.0f, 1.0f, 1.0f);
})EOT";
	m_defVS = std::make_shared<VertexShader>();
	m_defVS->Compile(vsCode);
	m_defPS = std::make_shared<PixelShader>();
	m_defPS->Compile(psCode);
}
