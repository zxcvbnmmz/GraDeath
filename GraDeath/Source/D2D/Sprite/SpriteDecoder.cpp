#include <d2d1.h>
#include "D2D/Sprite/SpriteDecoder.h"
#include "D2D/Interface/D2DRenderTarget.h"
#include "D2D/Interface/ImagingFactory.h"
#include <assert.h>
#include <wincodec.h>


bool D2D::CreateSprite(ID2D1Bitmap** _bitmap, LPCWSTR _fileName){
	assert(_fileName != NULL);


	CComQIPtr<IWICBitmapDecoder> dec;
	CComQIPtr<IWICImagingFactory> imagingFactory = D2D::ImagingFactory::Get();
	if (FAILED(D2D::ImagingFactory::Get()->CreateDecoderFromFilename(_fileName, NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &dec))){
		return false;
	};

	CComQIPtr<IWICBitmapFrameDecode> frame;
	dec->GetFrame(0, &frame);

	CComQIPtr<IWICFormatConverter> converter;
	imagingFactory->CreateFormatConverter(&converter);
	converter->Initialize(frame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.f, WICBitmapPaletteTypeMedianCut);

	if (FAILED(D2D::RenderTarget::Get()->CreateBitmapFromWicBitmap(converter, NULL, _bitmap))){
		return false;
	}

	return true;
}
