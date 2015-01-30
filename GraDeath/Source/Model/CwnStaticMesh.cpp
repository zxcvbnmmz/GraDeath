// fliename	CwnStaticMesh.cpp
// brief	�Ǝ��t�H�[�}�b�g�X�L�����b�V��
// name		����@�T
// memo
// 2013.10.21
// ************************************************************

// �C���N���[�h ***********************************************
#include "Graphic/D3DGraphic.h"
#include "Graphic/Sampler/Sampler.h"
#include "Graphic/ShaderResource/ShaderResource.h"
#include "Model/CwnStaticMesh.h"
#include "Model/CwnDecoder.h"
#include "Model/MeshDef.h"
#include "Model/ModelStaticShader.h"


// �`��
void CwnStaticMesh::Render ( Shader* shader, ModelStaticDatas* fscb )
{
	if ( !meshData ) return;

	ModelStaticDatas mds;

	for ( DWORD num = 0; num < meshData->numMesh; num++ )
	{
		// ���_�o�b�t�@���Z�b�g
		meshData->meshs[ num ].vertexBuffer.SetToIA();

		// �C���f�b�N�X�o�b�t�@���Z�b�g
		meshData->meshs[ num ].indexBuffer.SetToIA ();

		for ( DWORD i = 0; i < meshData->meshs[ num ].numMaterial; i++ )
		{
			mds.data.light = fscb->data.light;
			mds.data.world = fscb->data.world;
			mds.data.wvp = fscb->data.wvp;

			mds.data.ambient = meshData->meshs[num].material[i].ambient;
			mds.data.diffuse = meshData->meshs[num].material[i].diffuse;
			mds.data.specular = meshData->meshs[num].material[i].specular;

			shader->SetParameters ( &mds );

			if ( meshData->meshs[ num ].material[ meshData->meshs[ num ].subSet[ i ].matIndex ].m_texture != nullptr )
			{
				// �T���v�����O�X�e�[�g��n��
				Sampler::SetLinearWrap ();

				// �e�N�X�`����n��
				meshData->meshs[ num ].material[ meshData->meshs[ num ].subSet[ i ].matIndex ].m_texture->SetToShader ( 0, 1 );
			}

			// �v���~�e�B�u�E�g�|���W�[��ݒ�
			Graphic::D3D::IA::SetPrimitiveTopology ( D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

			// �}�e���A���̊e�v�f���G�t�F�N�g�ɓn��
			Graphic::D3D::Draw (
				meshData->meshs[ num ].subSet[ i ].faceCount,
				meshData->meshs[ num ].subSet[ i ].faceStart,
				0 );
		}
	}
}