struct PS_IN
{
	float4 pos : SV_POSITION0;
	float2 uv : TEXCOORD0;
	float4 color : COLOR0;
};

Texture2D tex : register(t0);
SamplerState samp : register(s0);

float4 main(PS_IN pin) : SV_TARGET
{
	float4 color = float4(0.0f, 0.0f, 0.0f, 1.0f);
	
	//解像度を下げてドット絵のような表現
	//UVのサイズを上げて、整数部分切り捨て
	float2 dotScreenSize = float2(16.0f, 9.0f);
	float rate = 10.0f;
	dotScreenSize *= rate;
	float2 i_uv = pin.uv * dotScreenSize;
	i_uv = floor(i_uv);	//小数の切り捨て

	//大きくなっているUVの大きさを元に戻す
	//※小数部分は切り捨ててるのでブロックごとのUV指定になる
	i_uv /= dotScreenSize;

	//ブロックごとになったUV値でテクスチャの色取得
	color = tex.Sample(samp, i_uv);
	return color;
}