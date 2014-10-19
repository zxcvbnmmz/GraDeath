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
#include "Model/ModelStaticShader.h"


// 描画
void CwnStaticMesh::Render ( Shader* shader, ModelStaticDatas* fscb )
{
	if ( !meshData ) return;

	//ModelStaticDatas mds;

	for ( unsigned int num = 0; num < meshData->numMesh; num++ )
	{
		// 頂点バッファをセット
		meshData->meshs[ num ].vertexBuffer.SetToIA();

		// インデックスバッファをセット
		meshData->meshs[ num ].indexBuffer.SetToIA ();

		for ( unsigned int i = 0; i < meshData->meshs[ num ].numMaterial; i++ )
		{
			fscb->bufferData.ambient = meshData->meshs[ num ].material[ i ].ambient;
			fscb->bufferData.diffuse = meshData->meshs[ num ].material[ i ].diffuse;
			fscb->bufferData.specular = meshData->meshs[ num ].material[ i ].specular;

			/*
			mds.gameData.lightDir = fscb->gameData.lightDir;
			mds.gameData.eye = fscb->gameData.eye;

			mds.bufferData.world = fscb->bufferData.world;
			mds.bufferData.wvp = fscb->bufferData.wvp;
			mds.bufferData.ambient = meshData->meshs[ num ].material[ i ].ambient;
			mds.bufferData.diffuse = meshData->meshs[ num ].material[ i ].diffuse;
			mds.bufferData.specular = meshData->meshs[ num ].material[ i ].specular;
			*/

			shader->SetParameters( fscb );

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