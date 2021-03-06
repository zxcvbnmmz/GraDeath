// ************************************************************
// fliename	CwnBaseMesh.h
// brief	独自フォーマットベースメッシュ
// name		川口　裕
// memo
// 2013.10.21
// ************************************************************

// 多重インクルード防止 ***************************************
#ifndef	_CWN_BASEMESH_H_
#define	_CWN_BASEMESH_H_


// 前方宣言 ***************************************************
class CwnDecoder;
class Texture;
struct MeshData;
struct MeshTextures;
namespace Graphic
{
	class ShaderResource;
}



// ************************************************************
// class	CwnBaseMesh
// brief	独自フォーマット読込
// ************************************************************
class CwnBaseMesh{
protected:
	CwnDecoder* decoder;	// 解読用
	MeshData*	meshData;

public:
	// ************************************************************
	// コンストラクタ
	// ************************************************************
	CwnBaseMesh();

	// ************************************************************
	// デストラクタ
	// ************************************************************
	virtual ~CwnBaseMesh();

	// ************************************************************
	// 解放
	// ************************************************************
	void Release();

	// ************************************************************
	// 読込
	// ************************************************************
	bool LoadCwn( char* filename, char* path );

	// ************************************************************
	// メッシュデータの取得
	// ************************************************************
	const MeshData* GetMesh();

	// ************************************************************
	// テクスチャのアタッチ
	// ************************************************************
	bool SetAttachingTexture( const MeshTextures* textures );
	bool SetAttachingTexture ( Graphic::ShaderResource* inTexture );
	bool SetAttachingTexture ( Graphic::ShaderResource* inTexture, int numMesh, int numMat );

};

#endif