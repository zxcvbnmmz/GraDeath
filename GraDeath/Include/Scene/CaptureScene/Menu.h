// ************************************************************
// filename	Menu.h
// brief	Menu
// name		����@�T
// memo
// 2014.01.21
// ************************************************************

// ���d�C���N���[�h�h�~ ***************************************
#ifndef _MENU_H_
#define _MENU_H_

// �C���N���[�h ***********************************************
#include "Scene\Scene.h"
#include "D2D/Text/TextObject.h"
#include "CaptureCamera.h"

// �O���錾 ***************************************************
class ModelAnimeLoader;

// ************************************************************
// class	Menu
// brief	Menu
// ************************************************************
class Menu{
private:

	class KeyboardOperation*	keyOpe;
	ModelAnimeLoader*	modelLoader;

	bool fontModel;
	bool fontAnime;
	bool modelDrawFlg;
	bool pushFlg;

	int selectNum;

	void (Menu::*DrawFunc[2])();	// �Ǎ��p�X�V�|�C���^

public:
	Menu();

	~Menu();

	int Update();

	void Draw();

private:
	void DrawModel();
	void DrawAnime();
	void DrawLoadModel();

	void CaptureAnimation();
	void ExecuteToScreenShot();
	bool isCapturing;

	::D2D::TextObject textObject;
	CaptureCamera captureCamera;
};

#endif