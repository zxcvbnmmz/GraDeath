// ************************************************************
// filename	CaptureScene.cpp
// brief	CaptureScene
// name		川口　裕
// memo
// 2014.01.21
// ************************************************************

// インクルード ***********************************************
#include "Scene/CaptureScene/CaptureScene.h"
#include "Input/Keyboard.h"
#include "D2D/Brush/SolidBrush.h"

// コンストラクタ
CaptureScene::CaptureScene()
{
	textObject.format = ::D2D::TextFormat::Create(L"メオリオ", 20.0f);
	textObject.brush = SolidBrush::Create(1, 1, 1, 1);
}

// デストラクタ
CaptureScene::~CaptureScene()
{
}

// 更新
SCENE_STATUS CaptureScene::Execute()
{
	menu.Update();

	return STILL_PROCESSING;
}

// 描画
void CaptureScene::Draw()
{
	textObject.DrawString(0, 0, L"Scene : CaptureScene");
	menu.Draw();
}

// 生成
Scene* CaptureScene::Create()
{
	return new CaptureScene;
}
