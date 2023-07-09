//	2Dの板ポリゴンなので、3Dとは別のデータが渡される
struct PS_IN{
	float4 pos : SV_POSITION0;
	float2 uv : TEXCOORD0;
	float4 color : COLOR0;
};

cbuffer Parameter : register(b0)
{
	float innerDistance;	//	内側の縁の距離
	float outerDistance;	//	外側の緑の距離
	float gageRate;			//	ゲージの現在量
	float dummy;			//	未使用
};

Texture2D tex : register(t0);
SamplerState samp : register(s0);

float4 main(PS_IN pin) : SV_TARGET
{
	float4 color = float4(0.0f, 0.0f, 0.0f, 0.0f);

	//	UVの値から、中心までの距離を求める
	float2 center = float2(0.5f, 0.5f);
	float2 offset = pin.uv - center;
	float r = length(offset);

	//	中心からの距離から表示するかしないか判定
	//	ただしif文を使うと全てのピクセルで計算することになるので、
	//	if文を使わずに表示の判定(計算)を行う
	//	step ... 左の数値(定数)より、右の数値が大きければ
	//	1,そうでなければ0を返す
	float inner = 1.0f -  step(innerDistance, r);
	float outer = step(outerDistance, r);
	color.a = inner * outer;


	//	極座標の角度を求める
	float pi = 3.141592f;
	float rad = atan2(offset.y, offset.x);	//	座標から角度を計算
	rad -= pi * 0.5f;			//	角度を変えてゲージのスタート地点を変更
	rad /= pi;					//	-3.14～3.14を-1～1に変換
	rad = rad * 0.5f + 0.5f;	//	-1～1を0～1に変換
	rad = frac(rad);	//	ゲージのスタート地点の変更で0.25～1.25になってる
						//	ので、frac関数で小数部分だけを取り出す。
	float gage = rad;
	gage = 1.0f - step(gageRate, gage);
	float3 frontColor = float3(0.0f, 1.0f, 0.3f);
	float3 backColor = float3(0.3f, 0.3f, 0.3f);

	//	UV座標に極座標の(角度、距離)を設定すると、
	//	引き延ばされてテクスチャが貼り付けられる。
	frontColor = tex.Sample(samp, float2(rad, r * 2.0f));

	color.rgb = lerp(backColor, frontColor, gage);


	return color;
}