#pragma once
#include "Shader.h"
#include <vector>

class ShaderManeger
{
public:
	enum class VSKind
	{
		E_VS_OBJECT = 0,
		E_VS_MAX,
	};

	enum class PSKind
	{
		E_PS_TEXCOLOR = 0,
		E_PS_MAX,
	};

public:
	static ShaderManeger& GetInstance();

	static VertexShader* GetVSShader(VSKind kind);
	static PixelShader* GetPSShader(PSKind kind);

private:
	ShaderManeger();
	~ShaderManeger();

	static std::vector<VertexShader*> m_pVSList;
	static std::vector<PixelShader*> m_pPSList;
};

