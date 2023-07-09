#include "LightBase.h"
#include "Geometory.h"

LightBase::LightBase()
	: m_pos(0.0f, 0.0f, 0.0f)
	, m_direction(0.0f, -1.0f, 0.0f)
	, m_diffuse(1.0f, 1.0f, 1.0f, 1.0f)
	, m_ambient(0.3f, 0.3f, 0.3f, 1.0f)
{
}
LightBase::~LightBase()
{
}

#ifdef _DEBUG
void LightBase::Draw()
{
	DirectX::XMFLOAT3 end(
		m_pos.x + m_direction.x,
		m_pos.y + m_direction.y,
		m_pos.z + m_direction.z
	);
	Geometory::SetColor(m_diffuse);
	Geometory::AddLine(m_pos, end);
	Geometory::DrawLines();

	DirectX::XMFLOAT4X4 mat;
	DirectX::XMStoreFloat4x4(&mat, DirectX::XMMatrixTranspose(
		DirectX::XMMatrixScaling(0.1f, 0.1f, 0.1f) *
		DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z)
	));
	Geometory::SetWorld(mat);
	Geometory::DrawBox();
}
#endif

DirectX::XMFLOAT3 LightBase::GetPos()
{
	return m_pos;
}
DirectX::XMFLOAT3 LightBase::GetDirection()
{
	return m_direction;
}
DirectX::XMFLOAT4 LightBase::GetDiffuse()
{
	return m_diffuse;
}
DirectX::XMFLOAT4 LightBase::GetAmbient()
{
	return m_ambient;
}

void LightBase::SetPos(DirectX::XMFLOAT3 pos)
{
	m_pos = pos;
}
void LightBase::SetDirection(DirectX::XMFLOAT3 dir)
{
	m_direction = dir;
}
void LightBase::SetDiffuse(DirectX::XMFLOAT4 color)
{
	m_diffuse = color;
}
void LightBase::SetAmbient(DirectX::XMFLOAT4 color)
{
	m_ambient = color;
}