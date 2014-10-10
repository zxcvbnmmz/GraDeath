#include "System/D2DCore.h"
#include "Graphic/D2DGraphic.h"
#include "D3D/SwapChain/SwapChain.h"
#include <wincodec.h>
#include <atlbase.h>

namespace D2DCore{
	namespace{
		CComPtr<ID2D1Factory> factory;
		CComPtr<ID2D1RenderTarget> target;
		CComPtr<IWICImagingFactory> imagingFactory;
	}
}

void D2DCore::Destroy(){
	target.Release();
	imagingFactory.Release();
	factory.Release();
}

HRESULT D2DCore::Init(){
	if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory))){
		return E_FAIL;
	}
	CoInitialize(NULL);

	if (FAILED(CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, reinterpret_cast<void**>(&imagingFactory)))){
		MessageBox(NULL, L"", L"ImagingFactoryì¬‚ÉŽ¸”s", MB_OK);
		return E_FAIL;
	}

	IDXGISurface *pBackBuffer = NULL;
	D3D::SwapChain::GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));

	FLOAT dpiX;
	FLOAT dpiY;
	factory->GetDesktopDpi(&dpiX, &dpiY);
	D2D1_RENDER_TARGET_PROPERTIES props =
		D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT,
		D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED), dpiX, dpiY);

	if (FAILED(factory->CreateDxgiSurfaceRenderTarget(pBackBuffer, &props, &target))){
		return E_FAIL;
	}

	pBackBuffer->Release();

	Graphic::D2D::SetRenderTarget(target);

	return S_OK;
}

HRESULT D2DCore::CreateTexture(LPCWSTR fileName, ID2D1Bitmap** bitmap){
	if (fileName == NULL){
		return E_FAIL;
	}

	CComQIPtr<IWICBitmapDecoder> dec;
	if (FAILED(imagingFactory->CreateDecoderFromFilename(fileName, NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &dec))){
		return E_FAIL;
	};

	CComQIPtr<IWICBitmapFrameDecode> frame;
	dec->GetFrame(0, &frame);

	CComQIPtr<IWICFormatConverter> converter;
	imagingFactory->CreateFormatConverter(&converter);
	converter->Initialize(frame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.f, WICBitmapPaletteTypeMedianCut);

	target->CreateBitmapFromWicBitmap(converter, NULL, bitmap);

	return S_OK;
}

IWICImagingFactory* D2DCore::GetImagingFactory(){
	return imagingFactory;
}

ID2D1RenderTarget* D2DCore::GetRenderTarget(){
	return target;
}

ID2D1Bitmap* D2DCore::Func(HBITMAP* src, HPALETTE palette){
	IWICBitmap* bitmap;
	imagingFactory->CreateBitmapFromHBITMAP(*src, NULL, WICBitmapUsePremultipliedAlpha, &bitmap);

	CComQIPtr<IWICFormatConverter> converter;
	imagingFactory->CreateFormatConverter(&converter);

	D2D1_BITMAP_PROPERTIES p;
	//converter->Initialize(bitmap, GUID_WICPixelFormat8bppAlpha, WICBitmapDitherTypeNone, NULL, 0.f, WICBitmapPaletteTypeMedianCut);
	//p.pixelFormat.format = DXGI_FORMAT_A8_UNORM;
	//p.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;

	converter->Initialize(bitmap, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.f, WICBitmapPaletteTypeMedianCut);
	p.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM;
	p.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;

	p.dpiX = p.dpiY = 96;
	ID2D1Bitmap* d1bitmap;
	HRESULT hr = target->CreateBitmapFromWicBitmap(converter, &p, &d1bitmap);
	bitmap->Release();
	return d1bitmap;
}