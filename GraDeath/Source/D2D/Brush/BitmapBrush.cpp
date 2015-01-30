#include "D2D/Brush/BitmapBrush.h"
#include "Graphic/D2DGraphic.h"

BitmapBrush::BitmapBrush():brush(nullptr){
}

BitmapBrush::BitmapBrush(ID2D1Bitmap* _bitmap):brush(nullptr){
	Graphic::D2D::Brush::CreateBitmapBrush(&brush,_bitmap);
}

BitmapBrush::~BitmapBrush(){
}

void BitmapBrush::SetBitmap(ID2D1Bitmap* _bitmap){
	brush->SetBitmap(_bitmap);
}
