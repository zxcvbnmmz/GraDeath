#include "System/D2DCore.h"
#include "D3D/SwapChain/SwapChain.h"
#include <wincodec.h>
#include <atlbase.h>

#include "D2D/Interface/ImagingFactory.h"
#include "D2D/Interface/WriteFactory.h"
#include "D2D/Interface/D2DRenderTarget.h"

namespace{
	CComPtr<ID2D1Factory> factory;
}

void D2DCore::Destroy(){
	D2D::WriteFactory::Release();
	D2D::RenderTarget:: Release();
	D2D::ImagingFactory::Release();
	factory.Release();
}

HRESULT D2DCore::Init(){
	if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory))){
		return E_FAIL;
	}

	if (!D2D::ImagingFactory::Create()){
		return E_FAIL;
	}

	if (!D2D::RenderTarget::Create(factory)){
		return E_FAIL;
	}

	if (!D2D::WriteFactory::Create()){
		return E_FAIL;
	}

	D2D::RenderTarget::SetBackBuffer();
	
	return S_OK;
}


