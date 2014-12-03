#include "D2D/Brush/SolidBrush.h"
#include "D2D/Interface/D2DRenderTarget.h"
#include <d2d1.h>

SolidBrush* SolidBrush::Create(float r, float g, float b, float a){
	SolidBrush* brush = new SolidBrush;
	if (brush != nullptr){
		ObjectPoolManager::GetInstance()->GetCurrentPool()->Add(brush);
		D2D1_COLOR_F color = { r, g, b, a };
		D2D::RenderTarget::Get()->CreateSolidColorBrush(color, reinterpret_cast<ID2D1SolidColorBrush**>(&brush->brush));
		return brush;
	}
	return nullptr;
}

void SolidBrush::SetColor(const D2D1_COLOR_F& color){
	reinterpret_cast<ID2D1SolidColorBrush*>(brush)->SetColor(color);
}

void SolidBrush::SetColor(const D3DXVECTOR4& color){
	reinterpret_cast<ID2D1SolidColorBrush*>(brush)->SetColor(D2D1::ColorF::ColorF(color.x, color.y, color.z, color.w));
}

void SolidBrush::SetColor(const D3DXVECTOR3& color, float a){
	reinterpret_cast<ID2D1SolidColorBrush*>(brush)->SetColor(D2D1::ColorF::ColorF(color.x, color.y, color.z, a));
}

void SolidBrush::SetColor(float r, float g, float b, float a){
	reinterpret_cast<ID2D1SolidColorBrush*>(brush)->SetColor(D2D1::ColorF::ColorF(r, g, b, a));
}

ID2D1SolidColorBrush* SolidBrush::Get(){
	return reinterpret_cast<ID2D1SolidColorBrush*>(brush);
}