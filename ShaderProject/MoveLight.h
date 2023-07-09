/* 
* �y������@�z
* [L�L�[]�������Ȃ���A�ȉ��̃L�[�Ŋe������s��
* [AD�L�[] ���_�𒆐S��Y����]
* [WS�L�[] ���_�𒆐S�ɏc��]
* [�����L�[] �F�ʂ̕ύX(HSV��H��ύX)
* [�����L�[] �ʓx�Ɩ��x��ύX(1.0(�ʓx0/���x1)�`0.5f(�ʓx1/���x1)�`0.0f(�ʓx1/���x0))
*/

#ifndef __MOVE_LIGHT_H__
#define __MOVE_LIGHT_H__

#include "LightBase.h"

class MoveLight : public LightBase
{
public:
	MoveLight();
	~MoveLight();

	void Update() final;
	void UpdateParam();

	void SetRot(float xz, float y);
	float GetRotXZ();
	float GetRotY();

	void SetHSV(float h, float sv);
	float GetH();
	float GetSV();

private:
	DirectX::XMFLOAT4 HSV2Color(float h, float sv);

private:
	float m_radXZ;
	float m_radY;
	float m_hue;
	float m_saturationValue;
};

#endif // __MOVE_LIGHT_H__
