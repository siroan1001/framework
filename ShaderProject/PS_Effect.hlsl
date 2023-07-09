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
	color = tex.Sample(samp, pin.uv);

	float4 frame = float4(0.0f, 0.0f, 0.0f, 1.0f);
	float2 uv = pin.uv;
	//立体的に見せる影の計算
	//領域を／（ななめ）で区切って明るい部分と暗い部分を計算
	frame.rgb = step(uv.x + uv.y, 1.0f) * 0.7f;
	//領域を逆／で区切って、先ほどの明るさの結果と合成する
	frame.rgb += step(uv.y, uv.x) * 0.3f;

	//縁に当たる部分が１，それ以外が０になるように計算
	//中心を０，０とした座標で考える
	uv = uv - float2(0.5f, 0.5f);
	uv = abs(uv);
	float mask = step(0.3f, max(uv.x, uv.y));
	
	//事前に計算したパラメータを利用して、縁取り表示
	color = lerp(color, frame, mask);

	return color;
}