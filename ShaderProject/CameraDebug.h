#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "CameraBase.h"
#include <Windows.h>

class CameraDebug : public CameraBase
{
private:
	struct Argument
	{
		DirectX::XMFLOAT2 mouseMove;
		DirectX::XMVECTOR vCamFront;
		DirectX::XMVECTOR vCamSide;
		DirectX::XMVECTOR vCamUp;
		DirectX::XMVECTOR vCamPos;
		DirectX::XMVECTOR vCamLook;
		float focus;
	};
public:
	CameraDebug();
	~CameraDebug();
	void Update() final;

private:
	void UpdateState();
	void UpdateOrbit(Argument& arg);
	void UpdateTrack(Argument& arg);
	void UpdateDolly(Argument& arg);
	void UpdateFlight(Argument& arg);

private:
	int m_state;
	POINT m_oldPos;
};

#endif