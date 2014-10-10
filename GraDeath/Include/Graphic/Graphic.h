#ifndef _GRAPHIC_H__
#define _GRAPHIC_H__

#include <D3D10_1.h>

namespace Graphic{
	namespace D2D{
		void BeginDraw();
		HRESULT EndDraw();
		void Clear(float r, float g, float b, float a);
	}

	enum CLEAR_FLAG{
		CLEAR_DEPTH = 0x01l,
		CLEAR_STENCIL = 0x02l,
		CLEAR_DEPTH_STENCIL = CLEAR_DEPTH | CLEAR_STENCIL
	};

	void Present(UINT syncInterval, UINT flag);
	void Clear(CLEAR_FLAG flag = CLEAR_DEPTH_STENCIL);
	void SetClearColor(float r, float g, float b, float a);
};

#endif	