// ************************************************************
// fliename	CwnDecoder.h
// brief	�Ǝ��t�H�[�}�b�g�Ǎ�
// name		����@�T
// memo
// 2013.08.21
// ************************************************************

// ���d�C���N���[�h�h�~ ***************************************
#ifndef	_CWN_DECODER_H_
#define	_CWN_DECODER_H_

// �C���N���[�h ***********************************************


// �O���錾 ***************************************************
struct	MeshData;
struct  MeshVertex;
struct	MeshMaterial;
struct  MeshTextures;
struct  CwnMesh;
class	Shader;
struct	ModelConstantBuffer;
struct	ModelSkinConstantBuffer;


// ************************************************************
// class	CwnDecoder
// brief	�Ǝ��t�H�[�}�b�g�Ǎ�
// ************************************************************
class CwnDecoder{
private:
	MeshData*		meshData;	// ���b�V���f�[�^

	char*			filePath;	// �t�@�C���p�X(���f���Ǎ��p)
	wchar_t*		rootPath;	// ���[�g�p�X(�e�N�X�`���p)

	// ************************************************************
	// struct	CwnVertex
	// brief	�Ǎ��p�o�[�e�N�X
	// ************************************************************
	struct CwnVertex
	{
		float			pos[ 3 ];
		float			normal[ 3 ];
		float			uv[ 2 ];
		float			weight[ 4 ];
		unsigned int	matrixIndex[ 4 ];
	};

	// ************************************************************
	// struct	CwnMaterial
	// brief	�Ǎ��p�ގ�
	// ************************************************************
	struct CwnMaterial
	{
		float			ambient[ 3 ];		// �A���r�G���g
		float			diffuse[ 3 ];		// �f�B�t���[�Y
		float			specular[ 3 ];		// �X�y�L����
		float			alpha;				// ����
		float			power;				// �p���[
		unsigned int	numFace;			// �ʐ�
		char			textureFileName[ 20 ];
	};

public:
	// ************************************************************
	// �R���X�g���N�^
	// ************************************************************
	CwnDecoder();

	// ************************************************************
	// �f�X�g���N�^
	// ************************************************************
	~CwnDecoder();

	// ************************************************************
	// ���
	// ************************************************************
	void Release();

	// ************************************************************
	// �Ǎ�
	// ************************************************************
	bool LoadCwn( char* filename, char* path );

	// ************************************************************
	// ���b�V���f�[�^�̎擾
	// ************************************************************
	MeshData* GetMesh();

	// ************************************************************
	// �e�N�X�`���̃A�^�b�`
	// ************************************************************
	bool SetAttachingTexture( const MeshTextures* textures );

private:
	// ************************************************************
	// �o�[�e�N�X�̓Ǎ�
	// ************************************************************
	void LoadVertex( MeshVertex* outVert, CwnVertex* inVert, unsigned long numVert );

	// ************************************************************
	// �C���f�b�N�X�̓Ǎ�
	// ************************************************************
	void LoadIndex( unsigned short* inIndex, int inNum );

	// ************************************************************
	// �ގ��̓Ǎ�
	// ************************************************************
	void LoadMaterial( CwnMesh* outMesh, CwnMaterial* inMaterial );

	// ************************************************************
	// �}�e���A���̃R�s�[
	// ************************************************************
	void CopyMaterial( MeshMaterial& outMaterial, CwnMaterial& inMaterial );

};

// ���b�V���f�[�^�̎擾
inline MeshData* CwnDecoder::GetMesh()
{
	return meshData;
}

#endif