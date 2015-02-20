#include "Direction/Fade.h"
#include "D2D/Sprite/Sprite.h"
#include <System/Window.h>

Fade::Fade(LPCWSTR fileName){
	sprite = Sprite::Create();
	sprite->Create(fileName);

	int w, h;
	System::Window::GetWindowSize(&w, &h);
	sprite->SetSize((float)w, (float) h);
	sprite->SetPosition(0, 0);
}

Fade::~Fade(){
	//sprite->Release();
}

FADE_STATUS Fade::AddAlpha(float _alpha){
	alpha += _alpha;
	sprite->SetAlpha(alpha);

	if (alpha >= 1)
		return FADE_UNCLEAR;
	if (alpha <= 0)
		return FADE_CLEAR;

	return FADE_HALF_CLEAR;
}

void Fade::SetAlpha(float _alpha){
	alpha = _alpha;
	sprite->SetAlpha(alpha);
}

void Fade::Draw(){
	sprite->Draw();
}

void Fade::SetScale(float scale){
	sprite->SetScale(scale,scale);
}

void Fade::SetPosition(int x, int y){
	sprite->SetPosition(x,y);
}