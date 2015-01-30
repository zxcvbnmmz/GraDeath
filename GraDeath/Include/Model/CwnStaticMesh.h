// ************************************************************
// fliename	CwnStaticMesh.h
// brief	独自フォーマット静的メッシュ
// name		川口　裕
// memo
// 2013.10.21
// ************************************************************

// 多重インクルード防止 ***************************************
#ifndef	_CWN_STATICMESH_H_
#define	_CWN_STATICMESH_H_

// インクルード ***********************************************
#include "Model/CwnBaseMesh.h"


// 前方宣言 ***************************************************
class D3DGraphics;
class Shader;
struct ModelStaticDatas;

// ************************************************************
// class	CwnStaticMesh
// brief	独自フォーマット静的メッシュ
// ************************************************************
class CwnStaticMesh : public CwnBaseMesh{
public:
	// ************************************************************
	// コンストラクタ
	// ************************************************************
	CwnStaticMesh (){}

	// ************************************************************
	// デストラクタ
	// ************************************************************
	~CwnStaticMesh (){}

	// ************************************************************
	// 描画
	// ************************************************************
	void Render ( Shader* shader, ModelStaticDatas* fscb );

};

#endif