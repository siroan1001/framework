#include "ShaderManeger.h"

//ShaderManeger& ShaderManeger::GetInstance();
std::vector<VertexShader*> ShaderManeger::m_pVSList;
std::vector<PixelShader*> ShaderManeger::m_pPSList;

ShaderManeger& ShaderManeger::GetInstance()
{
	static ShaderManeger instance;
	return instance;
}

ShaderManeger::ShaderManeger()
{
	const char* VSfile[] = {
		"Assets/Shader/VS_Object.cso",
	};

	const char* PSfile[] = {
		"Assets/Shader/PS_TexColor.cso",
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

ShaderManeger::~ShaderManeger()
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

VertexShader* ShaderManeger::GetVSShader(VSKind kind)
{
	return m_pVSList[(int)kind];
}

PixelShader* ShaderManeger::GetPSShader(PSKind kind)
{
	return m_pPSList[(int)kind];
}