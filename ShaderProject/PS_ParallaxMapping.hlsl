struct PS_IN
{
    float4 pos : SV_POSITION0;
    float2 uv : TEXCOORD0;
    float3 normal : NORMAL0;
    float4 lightAmbient : VECTOR0;
    float3 lightT : NORMAL1;
    // 接ベクトル空間に移動させた視線の情報
    float3 camVecT : NORMAL2;
};
SamplerState samp : register(s0);
Texture2D tex : register(t0);
Texture2D normalMap : register(t1);
// ハイトマップ(高さ情報を含んだテクスチャ)
Texture2D heightMap : register(t2);

float4 main(PS_IN pin) : SV_TARGET
{
    float4 color = float4(0.0f, 0.0f, 0.0f, 1.0f);

    // 高さマップ取得
    float hScale = heightMap.Sample(samp, pin.uv).r;
    float height = 0.05f * hScale;
    // 接空間上で視線方向にどれだけ進むか
    float2 offset = -pin.camVecT.xy / pin.camVecT.z;
    offset *= height;

    // 法線マップから法線のデータを取得
    float3 N = normalMap.Sample(samp, pin.uv - offset).rgb;
    N = normalize(N * 2.0f - 1.0f);
    // 事前に計算されたテクスチャ空間のライト
    float3 L = normalize(pin.lightT);

    // 法線とライトから明るさを計算(今まで通り)
    float diffuse = saturate(dot(-L, N));
    color = tex.Sample(samp, pin.uv - offset);
    color.rgb = color.rgb * (diffuse + pin.lightAmbient.rgb);


    return color;
}