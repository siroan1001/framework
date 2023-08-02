#pragma once
#include "Shader.h"
#include <vector>
#include <DirectXMath.h>

class ShaderManager
{
public:
	enum class VSKind
	{
		E_VS_OBJECT = 0,
		E_VS_OUTLINE,
		E_VS_MAX,
	};

	enum class PSKind
	{
		E_PS_TEXCOLOR = 0,
		E_PS_COLOR,
		E_PS_OUTLINE,
		E_PS_MAX,
	};

	struct VS_OBJECT
	{

	};

	struct VS_OUTLINE
	{
		DirectX::XMFLOAT4X4 mat[3];
	};

	struct VS_BUF
	{
		union
		{
			ShaderManager::VS_OBJECT ObjectBuf;
			ShaderManager::VS_OUTLINE OutLineBuf;
		}Buf;
	};

	struct PS_TEXCOLOR_BUF
	{

	};

	struct PS_COLOR_BUF
	{
		DirectX::XMFLOAT3 color;
	};

	struct PS_OUTLINE_BUF
	{
		float outlineWidth;
	};



	struct PS_BUF
	{
		union
		{
			ShaderManager::PS_TEXCOLOR_BUF TexcolerBuf;
			ShaderManager::PS_COLOR_BUF ColorBuf;
			ShaderManager::PS_OUTLINE_BUF OutLineBuf;
		}Buf;
	};

public:
	static ShaderManager& GetInstance();

	static VertexShader* GetVSShader(VSKind kind);
	static PixelShader* GetPSShader(PSKind kind);

private:
	ShaderManager();
	~ShaderManager();

	static std::vector<VertexShader*> m_pVSList;
	static std::vector<PixelShader*> m_pPSList;
};

