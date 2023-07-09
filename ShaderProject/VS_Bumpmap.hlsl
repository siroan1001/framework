struct VS_IN
{
    float3 pos : POSITION0;
    float3 normal : NORMAL0;
    float2 uv : TEXCOORD0;
    // 接ベクトル（テクスチャを張り付けた際の
    float3 tangent : TANGENT0;
};
struct VS_OUT
{
    float4 pos : SV_POSITION0;
    float2 uv : TEXCOORD0;
    float3 normal : NORMAL0;
    float4 lightAmbient : VECTOR0;
    // 接ベクトル空間に移動させたライトの情報
    float3 lightT : NORMAL1;
    // 接ベクトル空間に移動させた視線の情報
    float3 camVecT : NORMAL2;
};

cbuffer WVP : register(b0)
{
    float4x4 world;
    float4x4 view;
    float4x4 proj;
};
cbuffer Light : register(b1) {
    float4 lightColor;
    float4 lightAmbient;
    float4 lightDir;
}
cbuffer Camera : register(b2) {
    float4 camPos;
}
//バンプマップについて調べたのですが、おそらく、VS_Bumpmapのテクスチャの法線をワールド空間に変換する処理がT, N, Bではなく, T, B, Nだと思います

VS_OUT main(VS_IN vin)
{
    VS_OUT vout;

    vout.pos = float4(vin.pos, 1.0f);
    vout.pos = mul(vout.pos, world);
    float4 worldPos = vout.pos; // 計算途中でワールド座標の情報を変数にコピー
    vout.pos = mul(vout.pos, view);
    vout.pos = mul(vout.pos, proj);

    vout.uv = vin.uv;

    vout.normal = mul(vin.normal, (float3x3)world);

    // 接ベクトルと面法線から従法線(Binormal)を計算
    float3 T = mul(vin.tangent, (float3x3)world);
    T = normalize(T);
    float3 N = normalize(vout.normal);
    float3 B = normalize(cross(T, N));
    // 3つのベクトルから、テクスチャの法線をワールド空間に変換するための行列
    float3x3 tangentMat = float3x3(T, B, N);

    // 法線との計算を行う光源のベクトルを、ワールド空間からテクスチャ空間へ移動させる
    // ※接ベクトルの変換行列の逆行列を求めればよい
    tangentMat = transpose(tangentMat);
    float3 invLightDir = normalize(lightDir.xyz);
    invLightDir = mul(invLightDir, tangentMat);
    vout.lightT = invLightDir;

    vout.lightAmbient = lightAmbient;

    // 視線ベクトルもワールド空間からテクスチャ空間へ移動させる
    float4 camVec = worldPos - camPos;
    vout.camVecT = mul(camVec.xyz, tangentMat);

    return vout;
}