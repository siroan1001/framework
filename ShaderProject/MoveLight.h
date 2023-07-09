/* 
* 【操作方法】
* [Lキー]を押しながら、以下のキーで各操作を行う
* [ADキー] 原点を中心にY軸回転
* [WSキー] 原点を中心に縦回転
* [←→キー] 色彩の変更(HSVのHを変更)
* [↑↓キー] 彩度と明度を変更(1.0(彩度0/明度1)～0.5f(彩度1/明度1)～0.0f(彩度1/明度0))
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
