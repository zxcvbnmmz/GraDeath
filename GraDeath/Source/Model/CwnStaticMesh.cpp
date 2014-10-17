// fliename	CwnStaticMesh.cpp
// brief	独自フォーマットスキンメッシュ
// name		川口　裕
// memo
// 2013.10.21
// ************************************************************

// インクルード ***********************************************
#include "Graphic/D3DGraphic.h"
#include "Model/CwnStaticMesh.h"
#include "Model/CwnDecoder.h"
#include "Graphic/Sampler/Sampler.h"
#include "Graphic/ShaderResource/ShaderResource.h"
#include "Model/MeshDef.h"
//#include "Shader.h"
//#include "ModelStaticShader.h"


// 描画
void CwnStaticMesh::Render( Shader* shader, ModelConstantBuffer* fscb )
{
	if ( !meshData ) return;

	//ModelConstantBuffer cb;

	for ( unsigned int num = 0; num < meshData->numMesh; num++ )
	{
		// 頂点バッファをセット
		meshData->meshs[ num ].vertexBuffer.SetToIA();

		// インデックスバッファをセット
		meshData->meshs[ num ].indexBuffer.SetToIA ();

		for ( unsigned int i = 0; i < meshData->meshs[ num ].numMaterial; i++ )
		{
			//cb.world	= fscb->world;										//	ワールド行列
			//cb.wvp		= fscb->wvp;										//	座標変換行列
			//cb.light	= fscb->light;										//	ライトベクトル
			//cb.ambient	= meshData->meshs[ num ].material[ i ].ambient;		//	アンビエント
			//cb.diffuse	= meshData->meshs[ num ].material[ i ].diffuse;		//	ディフューズ
			//cb.specular	= meshData->meshs[ num ].material[ i ].specular;		//	スペキュラ

			//shader->SetConstantBuffer( &cb );

			if ( meshData->meshs[ num ].material[ meshData->meshs[ num ].subSet[ i ].matIndex ].m_texture != NULL )
			{
				// サンプリングステートを渡す
				Sampler::SetLinearWrap ();

				// テクスチャを渡す
				meshData->meshs[ num ].material[ meshData->meshs[ num ].subSet[ i ].matIndex ].m_texture->SetToShader ( 0, 1 );
			}

			// プリミティブ・トポロジーを設定
			Graphic::D3D::IA::SetPrimitiveTopology ( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

			// マテリアルの各要素をエフェクトに渡す
			Graphic::D3D::Draw (
				meshData->meshs[ num ].subSet[ i ].faceCount,
				meshData->meshs[ num ].subSet[ i ].faceStart,
				0 );
		}
	}
}