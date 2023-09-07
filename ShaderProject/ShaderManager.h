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
		E_VS_SWP,
		E_VS_MAX,
	};

	enum class PSKind
	{
		E_PS_TEXCOLOR = 0,
		E_PS_GOURAUDSHADING,
		E_PS_FRAME,
		E_PS_MAX,
	};

	struct VS_OBJECT
	{
		DirectX::XMFLOAT4X4 world;
		DirectX::XMFLOAT4X4 view;
		DirectX::XMFLOAT4X4 proj;
	};

	struct VS_SWP
	{
		DirectX::XMFLOAT4X4 world;
		DirectX::XMFLOAT4X4 view;
		DirectX::XMFLOAT4X4 proj;
	};

	struct VS_BUF
	{
		union
		{
			ShaderManager::VS_OBJECT ObjectBuf;
			ShaderManager::VS_SWP SWPBuf;
		}Buf;
	};

	struct PS_TEXCOLOR_BUF
	{

	};

	struct PS_GOURAUDSHADING_BUF
	{

	};

	struct PS_FRAME_BUF
	{

	};

	struct PS_BUF
	{
		union
		{
			ShaderManager::PS_TEXCOLOR_BUF TexcolerBuf;
			ShaderManager::PS_GOURAUDSHADING_BUF GouraudBuf;
			ShaderManager::PS_FRAME_BUF FrameBuf;
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

