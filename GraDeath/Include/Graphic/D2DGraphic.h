#ifndef _D2DGRAPHIC_H__
#define _D2DGRAPHIC_H__

#include <d2d1.h>
#include <D3DX10math.h>

class SolidBrush;

namespace Graphic{
	namespace D2D{
		void SetRenderTarget(ID2D1RenderTarget* _target);
		void DrawBitmap(ID2D1Bitmap* bitmap, D2D1_RECT_F& rect);
		void DrawBitmap(ID2D1Bitmap* bitmap, D2D1_RECT_F& rect, float opacity);
		void DrawBitmap(ID2D1Bitmap* bitmap, D2D1_RECT_F& rect, float opacity, const D2D1::Matrix3x2F& rot);
		void DrawBitmap(ID2D1Bitmap* bitmap, D2D1_RECT_F& rect, float opacity, const D2D1::Matrix3x2F& rot, D2D1_RECT_F& src);

		void DrawFillMask(ID2D1Bitmap* bitmap,ID2D1Brush* brush);

		namespace Brush{
			HRESULT CreateBitmapBrush(ID2D1BitmapBrush** brush, ID2D1Bitmap* bitmap);
			HRESULT CreateRGBrush(ID2D1RadialGradientBrush** brush, ID2D1Bitmap* bitmap);
			HRESULT CreateLGBrush(ID2D1LinearGradientBrush** brush, ID2D1Bitmap* bitmap);
			HRESULT CreateSolidBrush(ID2D1SolidColorBrush** brush);
		};
	};
}

#endif	// end of D2DGraphic