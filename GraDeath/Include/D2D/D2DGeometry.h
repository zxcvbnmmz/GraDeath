#ifndef _D2D_GEOMETRY_H__
#define _D2D_GEOMETRY_H__

#include <D3DX10.h>

class Brush;

namespace Graphic{
	namespace D2D{
		namespace Geometry{
			void DrawLine(class Brush* brush, const D3DXVECTOR2& p1, const D3DXVECTOR2& p2, float width = 1.0f);
			void DrawLine(class Brush* brush, float px1, float py1, float px2, float py2, float width = 1.0f);
			void DrawRect(class Brush* brush, const D3DXVECTOR2& pos, const D3DXVECTOR2& size, bool fill = false);
			void DrawRect(class Brush* brush, float x, float y, const D3DXVECTOR2& size, bool fill = false);
			void DrawRect(class Brush* brush, float px, float py, float qx, float qy, bool fill = false);
			void DrawEllipse(class Brush* brush, const D3DXVECTOR2& center, float radius, bool fill = false);
			void DrawEllipse(class Brush* brush, float x, float y, float radius, bool fill = false);
			void DrawEllipse(class Brush* brush, const D3DXVECTOR2& center, const D3DXVECTOR2& radius, bool fill = false);
			void DrawEllipse(class Brush* brush, float x, float y, float radX, float radY, bool fill = false);
		}
	}
}

#endif	// end of D2DGeometry