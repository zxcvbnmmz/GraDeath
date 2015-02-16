#include "D2D/Sprite/Sprite.h"
#include "D2D/Sprite/SpriteDecoder.h"
#include <assert.h>
#include "Graphic/D2DGraphic.h"


Sprite::Sprite():alpha(1){
	bitmap = nullptr;
	scale = { 1, 1 };
	this->weight = { 0, 0 };
	reverseFlag = FLIP_NONE;
}

Sprite::~Sprite(){
	if (bitmap){
		bitmap->Release();
		bitmap = nullptr;
	}
}

bool Sprite::Create(LPCWSTR fileName){
	assert(bitmap == nullptr);

	if (!D2D::CreateSprite(&bitmap, fileName)){
		wchar_t str[80];
		wsprintf(str, L"%s ‚Ì“Ç‚Ýž‚Ý‚ÉŽ¸”s", fileName);
		MessageBox(NULL, L"ƒGƒ‰[", str, MB_OK);
		abort();
		return false;
	}

	SetDefaultSize();

	return true;
}

void Sprite::Draw(DRAW_EFFECT effect){
	D2D1_RECT_F _rect;
	_rect.left = pos.x - weight.x;
	_rect.top = pos.y - weight.y;
	_rect.right = _rect.left + size.width;
	_rect.bottom = _rect.top + size.height;

	D2D1_SIZE_F localScale = scale;
	if (reverseFlag & FLIP_HORIZONTAL){
		localScale.width *= -1;
	}
	if (reverseFlag & FLIP_VERTICAL){
		localScale.height *= -1;
	}

	D2D1::Matrix3x2F _rot, _scale, mat;
	mat = _rot = _scale = D2D1::Matrix3x2F::Identity();
	D2D1_POINT_2F center;

	center.x = (_rect.left + _rect.right) / 2;
	center.y = (_rect.top + _rect.bottom) / 2;
	_scale = D2D1::Matrix3x2F::Scale ( localScale, center );

	center.x = _rect.left + weight.x;
	center.y = _rect.top + weight.y;
	_rot = D2D1::Matrix3x2F::Rotation(degree, center);

	mat = _rot * _scale;

	if (effect & DRAW_NORMAL){
		Graphic::D2D::DrawBitmap(bitmap, _rect, alpha, mat);
	}else if(effect & DRAW_RECT){
		Graphic::D2D::DrawBitmap(bitmap, _rect, alpha, mat, trim);
	}else{
		D2D1::Matrix3x2F _skew = D2D1::Matrix3x2F::Skew(skew.x, skew.y, center);
		mat = _skew * mat;
		Graphic::D2D::DrawBitmap(bitmap, _rect, alpha, mat);
	}
}

void Sprite::SetAlpha(float _alpha){
	alpha = _alpha;
}

void Sprite::SetSize(float x, float y){
	size.width = x;
	size.height = y;
}

void Sprite::SetSize(const D3DXVECTOR2& vec){
	size.width = vec.x;
	size.height = vec.y;
}

void Sprite::SetSize(const D2D1_SIZE_F& _size){
	size = _size;
}

void Sprite::SetSizeX(float x){
	size.width = x;
}

void Sprite::SetSizeY(float y){
	size.height = y;
}

void Sprite::SetPosition(float x, float y){
	pos.x = x;
	pos.y = y;
}

void Sprite::SetPosition(const D3DXVECTOR2& vec){
	pos.x = vec.x;
	pos.y = vec.y;
}

void Sprite::SetPositionX(float x){
	pos.x = x;
}

void Sprite::SetPositionY(float y){
	pos.y = y;
}

void Sprite::SetDefaultSize(){
	size = bitmap->GetSize();
}

void Sprite::SetRotation(float _degree){
	degree = _degree;
}

void Sprite::SetSkew(float xDeg, float yDeg){
	skew.x = xDeg;
	skew.y = yDeg;
}

D3DXVECTOR2 Sprite::GetPosition(){
	return D3DXVECTOR2(pos.x, pos.y);
}

const D2D1_RECT_F* Sprite::GetSize(){
	return reinterpret_cast<const D2D1_RECT_F*>(&size);
}

D3DXVECTOR2 Sprite::GetDefaultSize(){
	return D3DXVECTOR2(bitmap->GetSize().width, bitmap->GetSize().height);
}

void Sprite::SetTrimming(int x, int y, int wSize, int hSize){
	trim.left = (float)x;
	trim.top = (float)y;
	trim.right = x + (float)wSize;
	trim.bottom = y + (float)hSize;
}

void Sprite::SetTrimming(const D2D1_RECT_F& rect){
	trim.left = rect.left;
	trim.top = rect.top;
	trim.right = rect.right + rect.left;
	trim.bottom = rect.bottom + rect.top;
}

void Sprite::SetScale(float x, float y){
	scale.width = x;
	scale.height = y;
}

void Sprite::SetWeight(int x, int y){
	weight.x = (float)x;
	weight.y = (float)y;
}

void Sprite::SetReverseFlag(REVERSE_FLAG flag){
	reverseFlag = flag;
}

bool Sprite::IsValid(){
	return bitmap != nullptr;
}