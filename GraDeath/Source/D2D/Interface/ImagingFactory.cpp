#include <D2D1.h>
#include "D2D/Interface/ImagingFactory.h"
#include <wincodec.h>
#include <assert.h>

namespace{
	CComPtr<IWICImagingFactory> imagingFactory;
}

using namespace D2D;

bool ImagingFactory::Create(){
	assert(imagingFactory == nullptr);

	if (FAILED(CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&imagingFactory)))){
		MessageBox(NULL, L"", L"ImagingFactoryçÏê¨Ç…é∏îs", MB_OK);
		return false;
	}

	return true;
}

void ImagingFactory::Release(){
	//imagingFactory.Release();
}

CComPtr<IWICImagingFactory> ImagingFactory::Get(){
	return imagingFactory;
}


