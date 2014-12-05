#include <D2D1.h>
#include "D2D/Text/TextObject.h"
#include "D2D/Interface/D2DRenderTarget.h"
#include "D2D/Brush/Brush.h"

void D2D::TextObject::DrawString(float x, float y, const wchar_t* str, ...){
	va_list list;
	wchar_t wsbuffer[256] = { 0 };

	va_start(list, str);
	int length = _vsnwprintf_s(wsbuffer, 256, str, list);
	va_end(list);

	float fontSize = format->format->GetFontSize();
	D2D1_RECT_F rect = D2D1::RectF(x, y, x + length * fontSize, y + fontSize);

	D2D::RenderTarget::Get()->DrawText(wsbuffer, length, format->format, &rect, brush->Get());
}

void D2D::TextObject::DrawLayout(float x, float y){
	D2D1_POINT_2F point = { x, y };
	D2D::RenderTarget::Get()->DrawTextLayout(point, layout->layout, brush->Get());
}
