// ************************************************************
// filename	CaptureScene.cpp
// brief	CaptureScene
// name		����@�T
// memo
// 2014.01.21
// ************************************************************

// �C���N���[�h ***********************************************
#include "Scene/CaptureScene/CaptureScene.h"
#include "Input/Keyboard.h"
#include "D2D/Brush/SolidBrush.h"

// �R���X�g���N�^
CaptureScene::CaptureScene()
{
	textObject.format = ::D2D::TextFormat::Create(L"���I���I", 20.0f);
	textObject.brush = SolidBrush::Create(1, 1, 1, 1);
}

// �f�X�g���N�^
CaptureScene::~CaptureScene()
{
}

// �X�V
SCENE_STATUS CaptureScene::Execute()
{
	menu.Update();

	return STILL_PROCESSING;
}

// �`��
void CaptureScene::Draw()
{
	textObject.DrawString(0, 0, L"Scene : CaptureScene");
	menu.Draw();
}

// ����
Scene* CaptureScene::Create()
{
	return new CaptureScene;
}
