#ifndef _SOLID_BRUSH_H__
#define _SOLID_BRUSH_H__

#include "Brush.h"
#include <D3DX10math.h>

class SolidBrush : public Brush{
public:
	SolidBrush(){}
	~SolidBrush(){}

	static SolidBrush* Create(float r, float g, float b, float a);
	ID2D1SolidColorBrush* Get();

	bool InitBrush(float r, float g, float b, float a);

	void SetColor(const D2D1_COLOR_F& color);
	void SetColor(const D3DXVECTOR4& color);
	void SetColor(const D3DXVECTOR3& color, float a = 1.0f);
	void SetColor(float r, float g, float b, float a = 1.0f);

};

#endif	// end of SolidBrush