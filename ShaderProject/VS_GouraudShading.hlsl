struct VS_IN{
	float3 pos : POSITION0;
	float3 normal : NORMAL0;
	float2 uv :TEXCOORD0;
};

struct VS_OUT {
	float4 pos : SV_POSITION0;
	float4 color : COLOR0;	//	頂点側で計算した明るさの情報
	float2 uv : TEXCOORD0;
};

cbuffer WVP : register(b0)
{
	float4x4 world;
	float4x4 view;
	float4x4 proj;
}

//	ライトの情報
cbuffer Light : register(b1)
{
	float4 lightColor;
	float4 lightAmbient;
	float4 lightDir;
}

VS_OUT main(VS_IN vin)
{
	VS_OUT vout;
	vout.pos = float4(vin.pos, 1.0f);
	vout.pos = mul(vout.pos, world);
	vout.pos = mul(vout.pos, view);
	vout.pos = mul(vout.pos, proj);

	//	頂点シェーダーで陰の計算
	float3 N = vin.normal;
	float3 L = lightDir.xyz;
	//	計算前に手を加える
	N = mul(N, (float3x3)world);
	L = -L;
	//	正規化
	N = normalize(N);
	L = normalize(L);
	//	陰計算
	float diffuse = saturate(dot(N, L));
	//	色決定
	vout.color = float4(diffuse + lightAmbient.rgb, 1.0f);


	vout.uv = vin.uv;


	return vout;
}