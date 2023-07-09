#ifndef __LIGHT_BASE_H__
#define __LIGHT_BASE_H__

#include <DirectXMath.h>

class LightBase
{
public:
	LightBase();
	~LightBase();

#ifdef _DEBUG
	void Draw();
#else
	void Draw() {}
#endif

	virtual void Update() = 0;

	DirectX::XMFLOAT3 GetPos();
	DirectX::XMFLOAT3 GetDirection();
	DirectX::XMFLOAT4 GetDiffuse();
	DirectX::XMFLOAT4 GetAmbient();


	void SetPos(DirectX::XMFLOAT3 pos);
	void SetDirection(DirectX::XMFLOAT3 dir);
	void SetDiffuse(DirectX::XMFLOAT4 color);
	void SetAmbient(DirectX::XMFLOAT4 color);

protected:
	DirectX::XMFLOAT3 m_pos;
	DirectX::XMFLOAT3 m_direction;
	DirectX::XMFLOAT4 m_diffuse;
	DirectX::XMFLOAT4 m_ambient;
};


#endif // __LIGHT_BASE_H__