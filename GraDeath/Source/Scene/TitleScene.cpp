#include "D2D/Sprite/Sprite.h"
#include "Scene/TitleScene.h"
#include "Graphic/Camera/Camera.h"
#include "System/Window.h"

#include "Scene/Factory/CharacterSelectFactory.h"
#include "Input/Gamepad.h"

Sprite sprite;

TitleScene::TitleScene(){

	int _w, _h;
	System::Window::GetWindowSize ( &_w, &_h );
	Graphic::Camera::SetViewport ( _w, _h );
	Graphic::Camera::SetPerspective ( ( float )D3DX_PI / 4.0f, (float)_w / (float)_h, 0.1f, 100.0f );
	Graphic::Camera::SetLookAt ( D3DXVECTOR3 (  0, 40 ,-60 ), D3DXVECTOR3 ( 0, 0, 0 ) );
	Graphic::Camera::Update ();

	sprite.Create(L"Resource/Texture/Test.png");
}

SCENE_STATUS TitleScene::Execute(){

	Graphic::Camera::Update ();
	if (GamePad::getAnyGamePadPressed(BUTTON_A)){
		CharacterSelectFactory cf;
		SceneFactory::Reserve(&cf);
		return END_PROCESS;
	}

	return STILL_PROCESSING;
}

void TitleScene::Draw(){

}
