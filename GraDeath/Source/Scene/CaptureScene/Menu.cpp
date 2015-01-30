// ************************************************************
// filename	CaptureScene.cpp
// brief	CaptureScene
// name		川口　裕
// memo
// 2014.01.21
// ************************************************************

// インクルード ***********************************************
#include "Scene/CaptureScene/Menu.h"
#include "Scene/CaptureScene/CaptureScene.h"
#include "Scene/CaptureScene/KeyboardOperation.h"
#include "Scene/CaptureScene/ModelAnimeLoader.h"
#include "Utility/ScreenShot.h"
#include "D2D/Brush/SolidBrush.h"
#include "Graphic/Rasterizer/Rasterizer.h"

enum VIEWER_MENU
{
	MENU_MODEL_LOAD = 0,
	MENU_ANIME_LOAD,
	MENU_MODEL_DRAW,
	MENU_ANIME_ATTACHI,
	MENU_MAX,
};

Menu::Menu() : fontModel(false), fontAnime(false), modelDrawFlg(false), isCapturing(false)
{
	// 描画用更新ポインタ
	DrawFunc[0] = &Menu::DrawModel;
	DrawFunc[1] = &Menu::DrawAnime;

	keyOpe = new KeyboardOperation;
	modelLoader = new ModelAnimeLoader;
	selectNum = MENU_MODEL_LOAD;
	keyOpe->SetUpDownMax(MENU_MAX);

	pushFlg = true;
	textObject.format = ::D2D::TextFormat::Create(L"メオリオ", 20.0f);
	textObject.brush = SolidBrush::Create(1, 1, 1, 1);

	Graphic::Rasterizer::CullNone();
}

Menu::~Menu()
{
	SafeDelete(keyOpe);
	SafeDelete(modelLoader);
}

int Menu::Update()
{
	if (keyOpe->GetKeyState(KC_SPACE, INPUT_PUSH) && !pushFlg)
	{
		pushFlg = true;
		fontModel = false;
		fontAnime = false;
		selectNum = MENU_MAX;
		modelLoader->SetModelFlg(false);
		modelLoader->SetAnimeFlg(false);
	}
	if (pushFlg)
	{
		keyOpe->Update();
		selectNum = keyOpe->GetUpDown();
	}

	modelLoader->Update();

	if (keyOpe->GetKeyState(KC_ENTER, INPUT_PUSH) && pushFlg)
	{
		pushFlg = false;
		switch (selectNum)
		{
		case MENU_MODEL_LOAD:
			modelLoader->Load(MENU_MODEL_LOAD);
			fontModel = true;
			break;

		case MENU_ANIME_LOAD:
			modelLoader->Load(MENU_ANIME_LOAD);
			fontAnime = true;
			break;

		case MENU_MODEL_DRAW:
			modelDrawFlg = true;
			modelLoader->SetModelDraw(modelDrawFlg);
			pushFlg = true;
			break;

		case MENU_ANIME_ATTACHI:
			modelLoader->SetAnimeAttachi(true);
			pushFlg = true;
			break;

		case MENU_MAX:
			break;
		}
	}

	captureCamera.Update();

	ExecuteToScreenShot();


	return 1;
}

void Menu::Draw()
{
	if (isCapturing){
		modelLoader->DrawModel();
		CaptureAnimation();
	}
	else{
		textObject.DrawString(20, 40, L"モデルの読込");
		textObject.DrawString(20, 60, L"アニメの読込");
		textObject.DrawString(20, 80, L"モデルの描画");
		textObject.DrawString(20, 100, L"アニメのアタッチ");
		textObject.DrawString(0, 40 + 20 * (float)selectNum, L"≫" );

		if ((fontModel || fontAnime) && !pushFlg)
		{
			modelLoader->DrawModelText(selectNum);
		}
		if (modelDrawFlg)
		{
			modelLoader->DrawModel();
		}

		captureCamera.DrawDetail();
	}
}

void Menu::DrawModel()
{
}

void Menu::DrawAnime()
{
}

void Menu::DrawLoadModel()
{
}

void Menu::ExecuteToScreenShot(){
	if (!isCapturing && keyOpe->GetKeyState(KC_P, INPUT_PUSH)){
		isCapturing = true;
		modelLoader->ResetAnimateTime();
	}

}

void Menu::CaptureAnimation(){
	static int captureFrame = 0;
	if (isCapturing){
		if (!modelLoader->IsAnimationEnd()){
			if(captureFrame % 2 == 0)
				Utility::CreateScreenShot(L"Resource/ScreenShot/");
			++captureFrame;
		}
		else{
			isCapturing = false;
			captureFrame = 0;
		}
	}
} 