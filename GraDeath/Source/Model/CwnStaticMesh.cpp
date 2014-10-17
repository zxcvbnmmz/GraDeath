// fliename	CwnStaticMesh.cpp
// brief	�Ǝ��t�H�[�}�b�g�X�L�����b�V��
// name		����@�T
// memo
// 2013.10.21
// ************************************************************

// �C���N���[�h ***********************************************
#include "Graphic/D3DGraphic.h"
#include "Model/CwnStaticMesh.h"
#include "Model/CwnDecoder.h"
#include "Graphic/Sampler/Sampler.h"
#include "Graphic/ShaderResource/ShaderResource.h"
#include "Model/MeshDef.h"
//#include "Shader.h"
//#include "ModelStaticShader.h"


// �`��
void CwnStaticMesh::Render( Shader* shader, ModelConstantBuffer* fscb )
{
	if ( !meshData ) return;

	//ModelConstantBuffer cb;

	for ( unsigned int num = 0; num < meshData->numMesh; num++ )
	{
		// ���_�o�b�t�@���Z�b�g
		meshData->meshs[ num ].vertexBuffer.SetToIA();

		// �C���f�b�N�X�o�b�t�@���Z�b�g
		meshData->meshs[ num ].indexBuffer.SetToIA ();

		for ( unsigned int i = 0; i < meshData->meshs[ num ].numMaterial; i++ )
		{
			//cb.world	= fscb->world;										//	���[���h�s��
			//cb.wvp		= fscb->wvp;										//	���W�ϊ��s��
			//cb.light	= fscb->light;										//	���C�g�x�N�g��
			//cb.ambient	= meshData->meshs[ num ].material[ i ].ambient;		//	�A���r�G���g
			//cb.diffuse	= meshData->meshs[ num ].material[ i ].diffuse;		//	�f�B�t���[�Y
			//cb.specular	= meshData->meshs[ num ].material[ i ].specular;		//	�X�y�L����

			//shader->SetConstantBuffer( &cb );

			if ( meshData->meshs[ num ].material[ meshData->meshs[ num ].subSet[ i ].matIndex ].m_texture != NULL )
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