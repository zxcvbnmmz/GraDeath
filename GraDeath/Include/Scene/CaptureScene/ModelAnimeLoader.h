// ************************************************************
// filename	ModelAnimeLoader.h
// brief	モデルローダー
// name		川口　裕
// memo
// 2014.01.16
// ************************************************************

// 多重インクルード防止 ***************************************
#ifndef	_MODEL_ANIME_LOADER_H_
#define	_MODEL_ANIME_LOADER_H_

// インクルード ***********************************************
#include <vector>
#include <string>
#include "D2D/Text/TextObject.h"


// 前方宣言 ***************************************************
class Shader;
class CwnSkinMesh;
class CwnBaseMesh;
class BoneAnimeData;
class FileLoader;
class KeyboardOperation;

enum MODEL_ANIME_LOAD
{
	LOOP = 0,
	MODEL_END,
	ANIME_END
};

// ************************************************************
// class	ModelAnimeLoader
// brief	モデルの読込
// ************************************************************
class ModelAnimeLoader
{
private:

	void (ModelAnimeLoader::*LoadFunc[2])();	// 読込用更新ポインタ
	void (ModelAnimeLoader::*DrawFunc[2])();	// 描画用更新ポインタ

	bool drawFlg;
	bool drawAnimeFlg;
	bool modelFlg;
	bool animeFlg;

	Shader*				skinShader;
	Shader*				staticShader;
	CwnBaseMesh*		mesh;
	BoneAnimeData*		animes;
	KeyboardOperation*	keyOpe;
	FileLoader*			loader;

	std::vector< std::string > fileModelList;
	std::vector< std::string > fileAnimeList;

	int modelNum;
	int animeNum;

public:
	// ************************************************************
	// コンストラクタ
	// ************************************************************
	ModelAnimeLoader();

	// ************************************************************
	// デストラクタ
	// ************************************************************
	~ModelAnimeLoader();

	// ************************************************************
	// 読込
	// ************************************************************
	void Load(int num);

	// ************************************************************
	// 更新
	// ************************************************************
	int Update();

	// ************************************************************
	// 描画
	// ************************************************************
	void DrawModel();

	void DrawModelText(int num);

	// ************************************************************
	// 解放
	// ************************************************************
	void Release();

	void SetModelDraw(bool model);
	void SetAnimeAttachi(bool anime);

	void SetModelFlg(bool flg);
	void SetAnimeFlg(bool flg);
	void ResetAnimateTime();
	bool IsAnimationEnd();

private:
	// ************************************************************
	// モデルローダー
	// ************************************************************
	void ModelLoader();
	void AnimeLoader();

	// ************************************************************
	// モデルの選択
	// ************************************************************
	void SelectModel();
	void SelectAnime();

	// ************************************************************
	// モデルネームの描画
	// ************************************************************
	void DrawModelName();
	void DrawAnimeName();

	::D2D::TextObject textObject;
};

inline void ModelAnimeLoader::SetModelFlg(bool flg)
{
	modelFlg = flg;
}

inline void ModelAnimeLoader::SetAnimeFlg(bool flg)
{
	animeFlg = flg;
}
#endif