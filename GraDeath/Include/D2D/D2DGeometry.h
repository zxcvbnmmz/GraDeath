#ifndef _D2D_GEOMETRY_H__
#define _D2D_GEOMETRY_H__

namespace Graphic{
	namespace D2D{
		namespace Geometry{
			void DrawLine(SolidBrush* brush, const D3DXVECTOR2& p1, const D3DXVECTOR2& p2, float width = 1.0f);
			void DrawLine(SolidBrush* brush, float px1, float py1, float px2, float py2, float width = 1.0f);
			void DrawRect(SolidBrush* brush, const D3DXVECTOR2& pos, const D3DXVECTOR2& size, bool fill = false);
			void DrawRect(SolidBrush* brush, float x, float y, const D3DXVECTOR2& size, bool fill = false);
			void DrawRect(SolidBrush* brush, float x, float y, float xSize, float ySize, bool fill = false);
			void DrawEllipse(SolidBrush* brush, const D3DXVECTOR2& center, float radius, bool fill = false);
			void DrawEllipse(SolidBrush* brush, float x, float y, float radius, bool fill = false);
			void DrawEllipse(SolidBrush* brush, const D3DXVECTOR2& center, const D3DXVECTOR2& radius, bool fill = false);
			void DrawEllipse(SolidBrush* brush, float x, float y, float radX, float radY, bool fill = false);
		};
	}
}

#endif	// end of D2DGeometry