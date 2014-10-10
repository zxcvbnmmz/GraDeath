#ifndef _BRUSH_H__
#define _BRUSH_H__

#include <atlbase.h>
#include <d2d1.h>

class Brush{
public:
	Brush();
	Brush(ID2D1Bitmap* _bitmap);
	virtual ~Brush();

protected:
	CComPtr<ID2D1Bitmap> bitmap;
};

#endif	// end of Brush