// ************************************************************
// filename	Menu.h
// brief	Menu
// name		川口　裕
// memo
// 2014.01.21
// ************************************************************

// 多重インクルード防止 ***************************************
#ifndef _MENU_H_
#define _MENU_H_

// インクルード ***********************************************
#include "Scene\Scene.h"
#include "D2D/Text/TextObject.h"
#include "CaptureCamera.h"

// 前方宣言 ***************************************************
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

	void (Menu::*DrawFunc[2])();	// 読込用更新ポインタ

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