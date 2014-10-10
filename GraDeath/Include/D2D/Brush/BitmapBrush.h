#ifndef _BITMAP_BRUSH_H__
#define _BITMAP_BRUSH_H__

#include "Brush.h"

struct ID2D1BitmapBrush;

class BitmapBrush : public Brush{
public:
	BitmapBrush();
	BitmapBrush(ID2D1Bitmap* bitmap);
	~BitmapBrush();

	void SetBitmap(ID2D1Bitmap* bitmap);

//private:
	CComPtr<ID2D1BitmapBrush> brush;
};

#endif	// end of BitmapBrush