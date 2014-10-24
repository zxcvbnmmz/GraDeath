#include <d2d1.h>
#include <d2d1helper.h>
#include "D2D/Interface/D2DRenderTarget.h"
#include "D3D/SwapChain/SwapChain.h"
#include <wincodec.h>
#include "Graphic/D2DGraphic.h"
#include <assert.h>

namespace{
	CComPtr<ID2D1RenderTarget> target;
}

using namespace D2D;

bool RenderTarget::Create(CComPtr<ID2D1Factory> _factory){
	assert(target == nullptr);
	assert(_factory != nullptr);

	IDXGISurface *pBackBuffer = NULL;
	D3D::SwapChain::GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));

	FLOAT dpiX;
	FLOAT dpiY;
	_factory->GetDesktopDpi(&dpiX, &dpiY);
	D2D1_RENDER_TARGET_PROPERTIES props =
		D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT,
		D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED), dpiX, dpiY);

	if (FAILED(_factory->CreateDxgiSurfaceRenderTarget(pBackBuffer, &props, &target))){
		return E_FAIL;
	}

	pBackBuffer->Release();

	return true;
}

void RenderTarget::Release(){
	target.Release();
}

CComPtr<ID2D1RenderTarget> RenderTarget::Get(){
	return target;
}

void RenderTarget::SetBackBuffer(){
	Graphic::D2D::SetRenderTarget(target);
}