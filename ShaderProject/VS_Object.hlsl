//	インプットレイアウト
//	CPUから渡される頂点の情報を定義したもの
struct VS_IN
{
	float3 pos : POSITION0;		//	セマンティクス
	float3 normal : NORMAL0;	//	データの用途を定義する
	float2 uv : TEXCOORD0;
};

//	頂点シェーダーからピクセルシェーダーへ送るデータの定義
struct VS_OUT
{
	float4 pos : SV_POSITION0;
	float2 uv : TEXCOORD0;
	float3 normal : NORMAL0;
};

//	定数バッファ
//	CPUとGPUでやり取りする、頂点以外のデータを格納する先
cbuffer WVP: register(b0)
{
	float4x4 world;
	float4x4 view;
	float4x4 proj;
};

VS_OUT main(VS_IN vin)
{
	VS_OUT vout;

	//	ローカル座標をスクリーン座標へ変換
	vout.pos = float4(vin.pos, 1.0f);	//	ローカル座標
	vout.pos = mul(vout.pos, world);	//	ワールド座標
	vout.pos = mul(vout.pos, view);		//	ビュー座標
	vout.pos = mul(vout.pos, proj);		//	プロジェクション座標

	//	ピクセルシェーダーで利用するUV座標を渡す
	vout.uv = vin.uv;

	//	ピクセルシェーダーで利用する法線を渡す
	//	法線はオブジェクトの回転に併せて回転させないとおかしな見た目になる。
	//	ワールド行列には移動成分も含まれるが、移動を法線に適用してもおかしく
	//	なるので、回転成分のみの行列となるように縮小して計算する。
	vout.normal = mul(vin.normal,(float3x3)world);

	return vout;
}