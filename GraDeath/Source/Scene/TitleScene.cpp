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

	start_pos = D3DXVECTOR2(700, 200);
	credit_pos = D3DXVECTOR2(800, 400);
	exit_pos = D3DXVECTOR2(800, 600);
	vect_pos = D3DXVECTOR2(600, 200);
	vect_move =
	start_move =
	credit_move =
	exit_move = D3DXVECTOR2(0, 0);
	tCount = 0;
	select_i = 0;
}

TitleScene::~TitleScene(){}

SCENE_STATUS TitleScene::Execute(){
	if (GamePad::getGamePadState(PAD_1, BUTTON_A, 0) == INPUT_PUSH ||
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
		vect_move += D3DXVECTOR2(0, -200);
		Move();
	}
	if (GamePad::getGamePadState(PAD_1, BUTTON_UP, 0) == INPUT_PUSH ||
#ifdef _DEBUG
		Keyboard::CheckKey(KC_UP) == INPUT_PUSH) {
#endif
		select_i--;
		vect_move += D3DXVECTOR2(0, 200);
		Move();
	}


	vect_move *= .85f;
	start_move *= .9f;
	credit_move *= .9f;
	exit_move *= .9f;

	return STILL_PROCESSING;
}

void TitleScene::Draw(){
	sVector.SetPosition(vect_pos + vect_move);
	switch (select_i){
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	}
	sStart.SetPosition(start_pos + start_move);
	sCredit.SetPosition(credit_pos + credit_move);
	sExit.SetPosition(exit_pos + exit_move);
	sStart.Draw();
	sCredit.Draw();
	sExit.Draw();
	sVector.SetPositionY(vect_pos.y + select_i * 200 + vect_move.y);
	sVector.Draw();

	// �`��
	// DrawLayout�͎��O�ɍ쐬���ꂽ���C�A�E�g���w��ʒu�ɕ`�悷��
	// DrawString�̓��C�A�E�g�͊֌W�Ȃ��ɁA�w��ʒu�Ɏ��R�ȕ�����`�悷��
	t.DrawLayout(0, 0);
	t.DrawString(0, 30, L"TextString");

}

void TitleScene::Move() {

	if (select_i < 0) {
		select_i = 2;
		vect_move = D3DXVECTOR2(0, -400);
	}
	else if (select_i >= 3)
	{
		select_i = 0;
		vect_move = D3DXVECTOR2(0, 400);
	}

	switch (select_i){
	case 0:
		start_move.x = 100;
		if(credit_pos.x == 700)credit_move.x -= 100;
		if (exit_pos.x == 700)exit_move.x -= 100;
		start_pos.x = 700;
		credit_pos.x = 800;
		exit_pos.x = 800;
		break;
	case 1:
		credit_move.x = 100;
		if(start_pos.x == 700)start_move.x -= 100;
		if (exit_pos.x == 700)exit_move.x -= 100;
		start_pos.x = 800;
		credit_pos.x = 700;
		exit_pos.x = 800;
		break;
	case 2:
		exit_move.x = 100;
		if (start_pos.x == 700)start_move.x -= 100;
		if (credit_pos.x == 700)credit_move.x -= 100;
		start_pos.x = 800;
		credit_pos.x = 800;
		exit_pos.x = 700;
		break;
	}
}