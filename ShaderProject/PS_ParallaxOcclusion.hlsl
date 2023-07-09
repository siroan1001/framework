struct PS_IN
{
    float4 pos : SV_POSITION0;
    float2 uv : TEXCOORD0;
    float3 normal : NORMAL0;
    float4 lightAmbient : VECTOR0;
    float3 lightT : NORMAL1;
    float3 camVecT : NORMAL2;
};
SamplerState samp : register(s0);
Texture2D tex : register(t0);
Texture2D normalMap : register(t1);
Texture2D heightMap : register(t2);

float4 main(PS_IN pin) : SV_TARGET
{
    float4 color = float4(0.0f, 0.0f, 0.0f, 1.0f);

    // ----- 視差遮蔽マッピング
    // ポリゴン面から視線方向に下がりながら、ハイトマップの高さと逆転する場所を探す
    // 高さが逆転する位置を探すためのループ回数
    int nStep = 100;
    float maxHeight = 0.05f;
    float stepHeight = maxHeight / nStep;

    // 接ベクトル上のUV座標の移動量を計算(1step当たりの高さの変化量にそろえる)
    float3 offset = pin.camVecT;
    offset.xy *= stepHeight / offset.z;
    offset.z = stepHeight;

    // 1ループで進む量が決まったので、ハイトマップの高さと逆転する位置まで進む
    float2 uv = pin.uv;
    float eyeHeight = maxHeight;
    // unroll...ループの最大回数を設定する
    [unroll(100)]for (int i = 0; i < nStep; ++i) {
        float height = heightMap.Sample(samp, uv).r;
        height *= maxHeight;
        if (height >= eyeHeight) {
            break;
        }
        // 視点の高さ、UVを移動させる
        uv -= offset.xy;
        eyeHeight -= offset.z;
    }

    // 法線マップから法線のデータを取得
    float3 N = normalMap.Sample(samp, uv).rgb;
    N = normalize(N * 2.0f - 1.0f);
    // 事前に計算されたテクスチャ空間のライト
    float3 L = normalize(pin.lightT);

    // 法線とライトから明るさを計算(今まで通り)
    float diffuse = saturate(dot(-L, N));
    color = tex.Sample(samp, uv);
    color.rgb = color.rgb * (diffuse + pin.lightAmbient.rgb);

    return color;
}