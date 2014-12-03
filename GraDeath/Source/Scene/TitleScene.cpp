#include "Scene/TitleScene.h"
#include "Graphic/Camera/Camera.h"
#include "System/Window.h"

#include "Scene/Factory/CharacterSelectFactory.h"
#include "Input/Gamepad.h"

#include "Input\Keyboard.h"

#include "D2D/Brush/SolidBrush.h"

TitleScene::TitleScene(){
	// �܂������`��ɓ�����t�H�[�}�b�g�i�t�H���g�Ƒ傫���j�����߂�
	t.format = D2D::TextFormat::Create(L"MS����", 30);

	// �������C�A�E�g�i�Œ�ʒu�ɌŒ蕶���j���g���̂Ȃ�A�t�H�[�}�b�g���g�p���ă��C�A�E�g���쐬
	// ������`�悷��̈敝�A�`�悷�镶�����ƕ������w�肷��
	t.layout = t.format->CreateLayout(300, 100, 13, L"TestLayout");

	// �����F��SolidBrush��Create�֐����g���쐬
	t.brush = SolidBrush::Create(255, 255, 255, 255);

	int _w, _h;
	System::Window::GetWindowSize ( &_w, &_h );
	Graphic::Camera::SetViewport ( _w, _h );
	Graphic::Camera::SetPerspective ( ( float )D3DX_PI / 4.0f, (float)_w / (float)_h, 0.1f, 100.0f );
	Graphic::Camera::SetLookAt ( D3DXVECTOR3 (  0, 40 ,-60 ), D3DXVECTOR3 ( 0, 0, 0 ) );
	Graphic::Camera::Update ();

	sStart.Create(L"Resource/Texture/Start.png");
	sCredit.Create(L"Resource/Texture/Credit.png");
	sExit.Create(L"Resource/Texture/Exit.png");
	sVector.Create(L"Resource/Texture/Vector.png");

	start_pos = D3DXVECTOR2(800, 200);
	credit_pos = D3DXVECTOR2(800, 400);
	exit_pos = D3DXVECTOR2(800, 600);
	vect_pos = D3DXVECTOR2(600, 200);
	select_pos = D3DXVECTOR2(100, 0);
	tCount = 0;
	select_i = 0;
}

TitleScene::~TitleScene(){}

SCENE_STATUS TitleScene::Execute(){
	if (GamePad::getGamePadState(PAD_1, BUTTON_DOWN, 0) == INPUT_PUSH ||
#ifdef _DEBUG
		Keyboard::CheckKey ( KC_ENTER ) == INPUT_PUSH ){
#endif
		switch (select_i){
		case 0:
			CharacterSelectFactory cf;
			SceneFactory::Reserve(&cf);
			return END_PROCESS;
			break;
		}
	}

	if (GamePad::getGamePadState(PAD_1, BUTTON_DOWN, 0) == INPUT_PUSH ||
#ifdef _DEBUG
		Keyboard::CheckKey(KC_DOWN) == INPUT_PUSH) {
#endif
		select_i++;
	}
	if (GamePad::getGamePadState(PAD_1, BUTTON_UP, 0) == INPUT_PUSH ||
#ifdef _DEBUG
		Keyboard::CheckKey(KC_UP) == INPUT_PUSH) {
#endif
		select_i--;
	}

	if (select_i < 0)
		select_i = 2;
	else if (select_i >= 3)
		select_i = 0;

	return STILL_PROCESSING;
}

void TitleScene::Draw(){
	sStart.SetPosition(start_pos);
	sCredit.SetPosition(credit_pos);
	sExit.SetPosition(exit_pos);
	sVector.SetPosition(vect_pos);
	switch (select_i){
	case 0:
		sStart.SetPosition(start_pos - select_pos);
		break;
	case 1:
		sCredit.SetPosition(credit_pos - select_pos);
		break;
	case 2:
		sExit.SetPosition(exit_pos - select_pos);
		break;
	}
	sStart.Draw();
	sCredit.Draw();
	sExit.Draw();
	sVector.SetPositionY(vect_pos.y + select_i * 200);
	sVector.Draw();

	// �`��
	// DrawLayout�͎��O�ɍ쐬���ꂽ���C�A�E�g���w��ʒu�ɕ`�悷��
	// DrawString�̓��C�A�E�g�͊֌W�Ȃ��ɁA�w��ʒu�Ɏ��R�ȕ�����`�悷��
	t.DrawLayout(0, 0);
	t.DrawString(0, 30, L"TextString");

}
