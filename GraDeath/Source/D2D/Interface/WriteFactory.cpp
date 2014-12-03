#include <D2D1.h>
#include "D2D/Interface/WriteFactory.h"
#include <wincodec.h>
#include <assert.h>
#include <dwrite.h>

#pragma comment(lib,"DWrite.lib")

namespace{
	CComPtr<IDWriteFactory> writeFactory;
}

using namespace D2D;

bool WriteFactory::Create(){
	assert(writeFactory == nullptr);

	if (FAILED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(writeFactory),
		reinterpret_cast< IUnknown** >(&writeFactory)))){
		return false;
	}


	return true;
}

void WriteFactory::Release(){
	//WriteFactory.Release();
}

CComPtr<IDWriteFactory> WriteFactory::Get(){
	return writeFactory;
}


