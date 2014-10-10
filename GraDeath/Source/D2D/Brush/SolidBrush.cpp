#include "D2D/Brush/SolidBrush.h"
#include <d2d1.h>

void SolidBrush::SetColor(const D2D1_COLOR_F& color){
	brush->SetColor(color);
}

void SolidBrush::SetColor(const D3DXVECTOR4& color){
	brush->SetColor(D2D1::ColorF::ColorF(color.x, color.y, color.z, color.w));
}

void SolidBrush::SetColor(const D3DXVECTOR3& color, float a){
	brush->SetColor(D2D1::ColorF::ColorF(color.x, color.y, color.z, a));
}

void SolidBrush::SetColor(float r, float g, float b, float a){
	brush->SetColor(D2D1::ColorF::ColorF(r, g, b, a));
}
