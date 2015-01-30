// ************************************************************
// filename	ModelAnimeLoader.h
// brief	���f�����[�_�[
// name		����@�T
// memo
// 2014.01.16
// ************************************************************

// ���d�C���N���[�h�h�~ ***************************************
#ifndef	_MODEL_ANIME_LOADER_H_
#define	_MODEL_ANIME_LOADER_H_

// �C���N���[�h ***********************************************
#include <vector>
#include <string>
#include "D2D/Text/TextObject.h"


// �O���錾 ***************************************************
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
// brief	���f���̓Ǎ�
// ************************************************************
class ModelAnimeLoader
{
private:

	void (ModelAnimeLoader::*LoadFunc[2])();	// �Ǎ��p�X�V�|�C���^
	void (ModelAnimeLoader::*DrawFunc[2])();	// �`��p�X�V�|�C���^

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
	// �R���X�g���N�^
	// ************************************************************
	ModelAnimeLoader();

	// ************************************************************
	// �f�X�g���N�^
	// ************************************************************
	~ModelAnimeLoader();

	// ************************************************************
	// �Ǎ�
	// ************************************************************
	void Load(int num);

	// ************************************************************
	// �X�V
	// ************************************************************
	int Update();

	// ************************************************************
	// �`��
	// ************************************************************
	void DrawModel();

	void DrawModelText(int num);

	// ************************************************************
	// ���
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
	// ���f�����[�_�[
	// ************************************************************
	void ModelLoader();
	void AnimeLoader();

	// ************************************************************
	// ���f���̑I��
	// ************************************************************
	void SelectModel();
	void SelectAnime();

	// ************************************************************
	// ���f���l�[���̕`��
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