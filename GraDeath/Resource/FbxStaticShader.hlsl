// テクスチャステート
Texture2D		texDecal: register( t0 );		// テクスチャ
SamplerState	samLinear : register( s0 );		// サンプラー

// グローバル変数群
cbuffer globalbuffer
{
	matrix world;		//	ワールド行列
	matrix wvp;			//	変換行列
	float4 ambient;		//	アンビエント(未使用)
	float4 diffuse;		//	ディフューズ
	float4 supecular;	//	スペキュラ(未使用)
	float4 light;		//	ライトベクトル
};

// バーテックスシェーダー出力構造体
struct VS_OUTPUT
{
	float4	pos		: SV_POSITION;
	float4	color	: NORMAL0;
	float2	uv		: TEXCOORD;
};

// バーテックスシェーダー
VS_OUTPUT FbxStaticShaderVS( float4 pos : POSITION, float4 norm : NORMAL, float2 uv : TEXCOORD )
{
	VS_OUTPUT output = ( VS_OUTPUT )0;

	// ライトのベクトル取得
	float3 lightDir = -light;

	// 法線をワールド行列で変換。x3にしているのは平行移動行列をなくすため
	// 法線、ライトベクトルの内積取得　normalize:正規化
	float3 normal	= normalize( mul( norm, ( float3x3 )world ) );
	lightDir = normalize( lightDir );

	// 座標変換
	output.pos		= mul( pos, wvp );

	// 法線、ライトベクトルの内積取得　normalize:正規化
	//normal = normalize( normal );
	//lightDir = normalize( lightDir );

	// dot:内積

	// 法線とライトベクトルの内積を取得 saturate:閾値０～１
	float4 NL = saturate( dot( normal, lightDir ) );
	NL.w = 1;

	// ディフューズカラーと乗算
	output.color = diffuse * NL;

	// テクスチャー座標取得
	output.uv = uv;

	return output;
}

// ピクセルシェーダー
float4 FbxStaticShaderPS( VS_OUTPUT input ) : SV_Target
{
	return texDecal.Sample( samLinear, input.uv );// * input.color;
}