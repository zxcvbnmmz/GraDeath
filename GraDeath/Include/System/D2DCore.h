#ifndef _D2D_CORE_H__
#define _D2D_CORE_H__

//#include "D2DWrite.h"
#include <d2d1.h>
#include <d2d1helper.h>

using namespace D2D1;

struct IWICImagingFactory;

namespace D2DCore{
	HRESULT Init();
	void Destroy();

	HRESULT CreateTexture(LPCWSTR fileName, ID2D1Bitmap** bitmap);


	ID2D1RenderTarget* GetRenderTarget();
	IWICImagingFactory* GetImagingFactory();

	ID2D1Bitmap* Func(HBITMAP* src, HPALETTE palette);
};


#endif	// end of D2DCore