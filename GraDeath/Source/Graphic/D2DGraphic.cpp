#include "Graphic/D2DGraphic.h"
#include "System/D2DCore.h"
#include "D2D/D2DGeometry.h"
#include "D2D/Brush/SolidBrush.h"

namespace Graphic{
	namespace D2D{
		namespace{
			ID2D1RenderTarget* target;
		};

		void SetRenderTarget(ID2D1RenderTarget* _target){
			target = _target;
		}

		void DrawBitmap(ID2D1Bitmap* bitmap, D2D1_RECT_F& rect){
			target->DrawBitmap(bitmap, rect);
		}

		void DrawBitmap(ID2D1Bitmap* bitmap, D2D1_RECT_F& rect, float opacity){
			target->DrawBitmap(bitmap, rect, opacity);
		}

		void DrawBitmap(ID2D1Bitmap* bitmap, D2D1_RECT_F& rect, float opacity, const Matrix3x2F& mat){
			target->SetTransform(mat);
			target->DrawBitmap(bitmap, rect, opacity);
			target->SetTransform(D2D1::Matrix3x2F::Identity());
		}

		void DrawBitmap(ID2D1Bitmap* bitmap, D2D1_RECT_F& rect, float opacity, const Matrix3x2F& mat, D2D1_RECT_F& src){
			target->SetTransform(mat);
			target->DrawBitmap(bitmap, rect, opacity, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, src);	
			target->SetTransform(D2D1::Matrix3x2F::Identity());
		}

		void DrawFillMask(ID2D1Bitmap* bitmap,ID2D1Brush* brush){
			D2D1_RECT_F rcBrushRect = D2D1::RectF(0, 0, bitmap->GetPixelSize().width, bitmap->GetPixelSize().height);
			target->SetAntialiasMode(D2D1_ANTIALIAS_MODE_ALIASED);
			target->FillOpacityMask(bitmap,brush,D2D1_OPACITY_MASK_CONTENT_GRAPHICS,&rcBrushRect,&rcBrushRect);
			target->SetAntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
		}

		void Geometry::DrawLine(SolidBrush* brush, const D3DXVECTOR2& _p1, const D3DXVECTOR2& _p2, float width){
			D2D1_POINT_2F p1 = {_p1.x,_p1.y};
			D2D1_POINT_2F p2 = {_p2.x,_p2.y};

			target->DrawLine(p1,p2,&(*brush),width);
		}

		void Geometry::DrawLine(SolidBrush* brush, float px1, float py1, float px2, float py2, float width){
			D2D1_POINT_2F p1 = {px1, py1};
			D2D1_POINT_2F p2 = {px2, py2};
			target->DrawLine(p1,p2,&(*brush),width);
		}

		void Geometry::DrawRect(SolidBrush* brush, const D3DXVECTOR2& pos, const D3DXVECTOR2& size, bool fill){
			D2D1_RECT_F rect = RectF(pos.x,pos.y,pos.x+size.x,pos.y+size.y);
			if(fill)
				target->FillRectangle(rect,&(*brush));
			else
				target->DrawRectangle(rect,&(*brush));}

		void Geometry::DrawRect(SolidBrush* brush, float x, float y, const D3DXVECTOR2& size, bool fill){
			D2D1_RECT_F rect = RectF(x,y,x+size.x,y+size.y);
			if(fill)
				target->FillRectangle(rect,&(*brush));
			else
				target->DrawRectangle(rect,&(*brush));
		}

		void Geometry::DrawRect(SolidBrush* brush, float x, float y, float xSize, float ySize, bool fill){
			D2D1_RECT_F rect = RectF(x,y,x+xSize,y+ySize);
			if(fill)
				target->FillRectangle(rect,&(*brush));
			else
				target->DrawRectangle(rect,&(*brush));}

		void Geometry::DrawEllipse(SolidBrush* brush, const D3DXVECTOR2& center, float radius, bool fill){
			D2D1_POINT_2F p = {center.x, center.y};
			D2D1_ELLIPSE ellipse = Ellipse(p,radius,radius);
			if(fill)
				target->FillEllipse(ellipse,&(*brush));
			else
				target->DrawEllipse(ellipse, &(*brush));
		}

		void Geometry::DrawEllipse(SolidBrush* brush, float x, float y, float radius, bool fill){
			D2D1_POINT_2F p = {x, y};
			D2D1_ELLIPSE ellipse = Ellipse(p,radius,radius);
			if(fill)
				target->FillEllipse(ellipse,&(*brush));
			else
				target->DrawEllipse(ellipse, &(*brush));
		}

		void Geometry::DrawEllipse(SolidBrush* brush, const D3DXVECTOR2& center, const D3DXVECTOR2& radius, bool fill){
			D2D1_POINT_2F p = {center.x, center.y};
			D2D1_ELLIPSE ellipse = Ellipse(p,radius.x,radius.y);
			if(fill)
				target->FillEllipse(ellipse,&(*brush));
			else
				target->DrawEllipse(ellipse, &(*brush));
		}

		void Geometry::DrawEllipse(SolidBrush* brush, float x, float y, float radX, float radY, bool fill){
			D2D1_POINT_2F p = {x, y};
			D2D1_ELLIPSE ellipse = Ellipse(p,radX,radY);
			if(fill)
				target->FillEllipse(ellipse,&(*brush));
			else
				target->DrawEllipse(ellipse, &(*brush));
		}

		void BeginDraw(){
			target->BeginDraw();
		}

		HRESULT EndDraw(){
			if(target->EndDraw() != D2DERR_RECREATE_TARGET)
				return S_OK;
			return E_FAIL;
		}

		void Clear(float r, float g, float b, float a){
			D2D1::ColorF color(r,g,b,a);
			target->Clear(color);
		}
		
		HRESULT Brush::CreateBitmapBrush(ID2D1BitmapBrush** brush, ID2D1Bitmap* bitmap){
			D2D1_BITMAP_BRUSH_PROPERTIES propertiesXClampYClamp = 
				D2D1::BitmapBrushProperties(D2D1_EXTEND_MODE_WRAP,D2D1_EXTEND_MODE_WRAP,
											D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
			return target->CreateBitmapBrush(bitmap,propertiesXClampYClamp,brush);
		}

		HRESULT Brush::CreateRGBrush(ID2D1RadialGradientBrush** brush, ID2D1Bitmap* bitmap){
			//target->CreateRadialGradientBrush(bitmap,&brush,);
			return S_OK;
		}
		
		HRESULT Brush::CreateLGBrush(ID2D1LinearGradientBrush** brush, ID2D1Bitmap* bitmap){
			//target->createl
			return S_OK;
		}
		
		HRESULT Brush::CreateSolidBrush(ID2D1SolidColorBrush** brush){
			return S_OK;
		}
	};
};