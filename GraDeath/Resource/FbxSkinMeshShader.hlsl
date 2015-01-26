//定義
#define MAX_BONE_MATRICES 255

//グローバル
Texture2D texDecal: register(t0);
SamplerState samLinear : register(s0);
SamplerState toonLinear : register(s1);

float4 m_LightDir = float4( 0, 1, 1, 1 );

cbuffer globalBuffer
{	
	matrix world;	//	ワールド行列
	matrix wvp;		//	ワールドから射影までの変換行列
    matrix constBoneWorld[MAX_BONE_MATRICES];	//	ボーン配列
};

//スキニング後の頂点・法線が入る
struct Skin
{
    float4 Pos;
    float3 Norm;
};

//	バーテックスバッファーの入力
struct VS_SkinIn
{
    float3 Pos	: POSITION;			//	座標
    float3 Norm : NORMAL;			//	法線
    float2 Tex	: TEXCOORD;			//	テクスチャ座標
    uint4  Bones : BONE_INDEX;		//	頂点に対応したボーンのインデックス
	float4 Weights : BONE_WEIGHT;	//	ボーンの重み
};

//ピクセルシェーダーの入力
struct PS_SkinIn
{
    float4 Pos	: SV_Position;		//	座標
    float3 Norm : NORMAL;			//	法線
    float2 Tex	: TEXCOORD;			//	テクスチャ座標
	float4 Color : COLOR0;			//	出力カラー
};

/**
	ウェイトに応じて頂点に対する姿勢行列を取得
 */
Skin SkinVert( VS_SkinIn Input )
{
	Skin Output = (Skin)0;

	float4 Pos = float4(Input.Pos,1);
	Pos.x*=-1;
    float3 Norm = Input.Norm;    

    //	ボーン0
    uint iBone = Input.Bones.x;
    float fWeight = Input.Weights.x;
    matrix m = constBoneWorld[ iBone ];
    Output.Pos += fWeight * mul( Pos, m );
    Output.Norm += fWeight * mul( Norm, (float3x3)m );    

    //	ボーン1
    iBone = Input.Bones.y;
    fWeight = Input.Weights.y;
    m = constBoneWorld[ iBone ];
    Output.Pos += fWeight * mul( Pos, m );
    Output.Norm += fWeight * mul( Norm, (float3x3)m );    

    //	ボーン2
    iBone = Input.Bones.z;
    fWeight = Input.Weights.z;
    m = constBoneWorld[ iBone ];
    Output.Pos += fWeight * mul( Pos, m );
    Output.Norm += fWeight * mul( Norm, (float3x3)m );    

    //	ボーン3
    iBone = Input.Bones.w;
    fWeight = Input.Weights.w;
    m = constBoneWorld[ iBone ];
    Output.Pos += fWeight * mul( Pos, m );
    Output.Norm += fWeight * mul( Norm, (float3x3)m );
    
    return Output;
}

/**
	頂点シェーダー
 */
PS_SkinIn SkinMeshVS( VS_SkinIn input )
{
    PS_SkinIn output;
    
	//	取得した姿勢行列を頂点に掛け合わせる
    Skin vSkinned = SkinVert( input );
	//vSkinned.Pos.z *= -1;

	//	行列変換を実行
    output.Pos = mul( vSkinned.Pos, wvp );

	//	法線の回転
    output.Norm = normalize( mul( vSkinned.Norm, ( float3x3 )world ) );

	//	テクスチャ座標取得
    output.Tex = input.Tex;

    return output;
}

//	ピクセルシェーダー
float4 SkinMeshPS(PS_SkinIn input) : SV_Target
{	
	//float4 Out;
//
	//// ハーフランバート拡散証明によるライティング計算
	//float p = dot( input.Norm, -m_LightDir.xyz );
	//p = p * 0.5f + 0.5f;
	////p = p * p;
//
	//// ************************************************************
	//// トゥーン処理
	//// ************************************************************
	//float4 Col = texDecal.Sample( toonLinear, float2( p, 0.0f ) );
//
	//Out = Col * texDecal.Sample( samLinear, input.Tex );
//
	//return Out;

	float4 TexDiffuse = texDecal.Sample ( samLinear, input.Tex );

	return TexDiffuse;
}