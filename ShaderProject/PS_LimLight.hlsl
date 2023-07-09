struct PS_IN{
	float4 pos : SV_POSITION0;
	float2 uv : TEXCOORD0;
	float3 normal : NORMAL0;
	float4 worldPos : POSITION0;
};
cbuffer Light : register(b0){
	float4 lightColor;
	float4 lightAmbient;
	float4 lightDir;
};
cbuffer Camera : register(b1){
	float4 camPos;	//	カメラのワールド座標
};

Texture2D tex : register(t0);
SamplerState samp : register(s0);

float4 main(PS_IN pin) : SV_TARGET
{
	float4 color = float4(0.0f, 0.0f, 0.0f, 1.0f);

	//	①逆光かどうか計算
	float3 L = normalize(lightDir.xyz);
	float3 V = normalize(camPos.xyz - pin.worldPos.xyz);
	float backLight = saturate(dot(L, V));

	//	②緑(法線に対して視線が垂直に当たる箇所)の計算
	float3 N = normalize(pin.normal);
	float edge = dot(N, V);
	edge = 1.0f - abs(edge);	//	垂直な部分が明るくなるように計算結果をひっくり返す
	edge = pow(edge, 5.0f);	//	緑部分のみを強調

	//	リムライトの計算
	float rim = backLight * edge;

	//	テクスチャ貼り付けて拡散光計算
	float diffuse = saturate(dot(N, -L));
	color = tex.Sample(samp, pin.uv);


	color.rgb = color.rgb * (diffuse + lightAmbient.rgb) + rim;

	return color;
}