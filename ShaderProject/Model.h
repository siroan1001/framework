#ifndef __MODEL_H__
#define __MODEL_H__

#include <DirectXMath.h>
#include <vector>
#include <memory>
#include <functional>
#include "Shader.h"
#include "MeshBuffer.h"
#include "Texture.h"

class Model
{
public:
	struct Vertex
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 normal;
		DirectX::XMFLOAT2 uv;
	};
	struct Material
	{
		DirectX::XMFLOAT4 diffuse;
		DirectX::XMFLOAT4 ambient;
		DirectX::XMFLOAT4 specular;
		std::shared_ptr<Texture> texture;
	};
	using Materials = std::vector<Material>;
	struct Mesh
	{
		std::shared_ptr<MeshBuffer> mesh;
		unsigned int materialID;
	};
	using Meshes = std::vector<Mesh>;

	struct RemakeInfo
	{
		UINT vtxNum;
		void* dest;
		const void* source;
		UINT idxNum;
		const void* idx;
	};

public:
	Model();
	~Model();
	void SetVertexShader(Shader* vs);
	void SetPixelShader(Shader* ps);
	const Mesh* GetMesh(unsigned int index);
	unsigned int GetMeshNum();

public:
	bool Load(const char* file, float scale = 1.0f, bool flip = false);
	void Draw(int texSlot = 0);
	
	void RemakeVertex(int vtxSize, std::function<void(RemakeInfo& data)> func);

private:
	void MakeDefaultShader();

private:
	static std::shared_ptr<VertexShader> m_defVS;
	static std::shared_ptr<PixelShader> m_defPS;
private:
	Meshes m_meshes;
	Materials m_materials;
	VertexShader* m_pVS;
	PixelShader* m_pPS;
};


#endif // __MODEL_H__