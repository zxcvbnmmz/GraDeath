#include "Scene/CaptureScene/CaptureCamera.h"
#include "Graphic/Camera/Camera.h"
#include <math.h>
#include "System/Window.h"
#include "Input/Keyboard.h"
#include "D2D/Brush/SolidBrush.h"

using namespace Graphic;

namespace{
	const static float ROTATE = 5.0f/180.0f*3.14159264f;
	const static float MOVE_VERTICAL = 5;
	const static float CLOSE_DISTANCE = 5;
}

CaptureCamera::CaptureCamera() :height(40.0f), distance(80.0f), rotate(0), lookHeight(0.0f), captureInterval(2) {
	Graphic::Camera::SetLookAt(D3DXVECTOR3(.0f, height, distance), D3DXVECTOR3(0.0f, lookHeight, 0.0f), D3DXVECTOR3(0, 1, 0));

	int x, y;
	System::Window::GetWindowSize(&x, &y);
	Graphic::Camera::SetViewport(x, y);
	Graphic::Camera::SetPerspective(60.0f / 180.0f*3.14159264f, (float)x / (float)y, 0.1, 1000.f);
	Graphic::Camera::Update();

	textObject.format = ::D2D::TextFormat::Create(L"メオリオ", 40.0f);
	textObject.brush = SolidBrush::Create(1, 1, 1, 1);

}

void CaptureCamera::Update(){
	RotateDegree();
	MoveVertical();
	CloseDistance();
	Reset();

	x = cos(rotate) * distance;
	z = sin(rotate) * distance;

	Graphic::Camera::SetLookAt(D3DXVECTOR3(x, height, z), D3DXVECTOR3(0.0f, lookHeight, 0.0f), D3DXVECTOR3(0, 1, 0));
	Graphic::Camera::Update();
}

void CaptureCamera::DrawDetail(){
	textObject.DrawString(0, 500, L"x = %f, y = %f, z = %f", x, height, z);
	textObject.DrawString(0, 530, L"rotate = %f", rotate);
	textObject.DrawString(0, 560, L"distance = %f", distance);
	textObject.DrawString(0, 590, L"lookAt = %f", lookHeight);
	textObject.DrawString(0, 630, L"回転 = A,D  上下移動 = W,S  ズーム = Shift+W,S  注視点上下移動 = E,Q");
}

void CaptureCamera::RotateDegree(){
	if (Keyboard::CheckKey(KC_A) == INPUT_PUSH){
		rotate += ROTATE;
	}
	else if (Keyboard::CheckKey(KC_D) == INPUT_PUSH){
		rotate -= ROTATE;
	}
}

void CaptureCamera::MoveVertical(){
	if (Keyboard::CheckKey(KC_W) == INPUT_PUSH){
		height += MOVE_VERTICAL;
	}
	else if (Keyboard::CheckKey(KC_S) == INPUT_PUSH){
		height -= MOVE_VERTICAL;
	}

	if (Keyboard::CheckKey(KC_E) == INPUT_PUSH){
		lookHeight -= MOVE_VERTICAL;
	}
	else if (Keyboard::CheckKey(KC_Q) == INPUT_PUSH){
		lookHeight += MOVE_VERTICAL;
	}
}

void CaptureCamera::CloseDistance(){
	if (Keyboard::CheckKey(KC_SHIFT) == INPUT_PRESS && Keyboard::CheckKey(KC_S) == INPUT_PUSH){
		distance += CLOSE_DISTANCE;
	}
	else if (Keyboard::CheckKey(KC_SHIFT) == INPUT_PRESS && Keyboard::CheckKey(KC_W) == INPUT_PUSH){
		distance -= CLOSE_DISTANCE;
	}
}

void CaptureCamera::Reset(){
	if (Keyboard::CheckKey(KC_R) == INPUT_PUSH){
		height = 40.0f;
		distance = 80.0f;
		rotate = 0.0f;
		lookHeight = 0.0f;
	}
}