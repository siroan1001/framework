#include "ShaderManager.h"

std::vector<VertexShader*> ShaderManager::m_pVSList;
std::vector<PixelShader*> ShaderManager::m_pPSList;

ShaderManager& ShaderManager::GetInstance()
{
	static ShaderManager instance;
	return instance;
}

ShaderManager::ShaderManager()
{
	const char* VSfile[] = {
		"Assets/Shader/VS_Object.cso",
		"Assets/Shader/VS_SpriteWorldPosition.cso",
	};

	const char* PSfile[] = {
		"Assets/Shader/PS_TexColor.cso",
		"Assets/Shader/PS_GouraudShading.cso",
		"Assets/Shader/PS_Frame.cso",
	};

	int num;
	num = _countof(VSfile);
	VertexShader* VS;
	for (int i = 0; i < num; i++)
	{
		VS = new VertexShader;
		VS->Load(VSfile[i]);
		m_pVSList.push_back(VS);
	}
	num = _countof(PSfile);
	PixelShader* PS;
	for (int i = 0; i < num; i++)
	{
		PS = new PixelShader;
		PS->Load(PSfile[i]);
		m_pPSList.push_back(PS);
	}
}

ShaderManager::~ShaderManager()
{
	for (VertexShader* VS : m_pVSList)
	{
		delete VS;
	}
	for (PixelShader* PS : m_pPSList)
	{
		delete PS;
	}
}

VertexShader* ShaderManager::GetVSShader(VSKind kind)
{
	return m_pVSList[(int)kind];
}

PixelShader* ShaderManager::GetPSShader(PSKind kind)
{
	return m_pPSList[(int)kind];
}