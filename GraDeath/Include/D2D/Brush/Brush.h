#ifndef _BRUSH_H__
#define _BRUSH_H__

#include <atlbase.h>
#include <d2d1.h>
#include "Pool/Ref.h"

class Brush : public Ref{
public:
	Brush();
	virtual ~Brush(){
		if (brush != nullptr){
			brush->Release();
			brush = nullptr;
		}
	}
	ID2D1Brush* Get(){return brush;}

protected:
	ID2D1Brush* brush;
};

#endif	// end of Brush