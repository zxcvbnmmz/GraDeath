#ifndef _D2D_RENDER_TARGET_H__
#define _D2D_RENDER_TARGET_H__

#include <atlbase.h>

struct ID2D1RenderTarget;
struct ID2D1Factory;

namespace D2D{
	namespace RenderTarget{
		bool Create(CComPtr<ID2D1Factory> _factory);
		void Release();
		void SetBackBuffer();
		CComPtr<ID2D1RenderTarget> Get();
	}
}

#endif	// end of D2DRenderTarget