#include <D3D10_1.h>
#include "D3D/Device/Device.h"
#include "D3D/SwapChain/SwapChain.h"

using namespace D3D;

#pragma comment(lib,"DXGI.lib")

std::shared_ptr<Device::Pimpl> Device::pimpl;

class Device::Pimpl{
public:
	Pimpl(){}
	bool Create();
	CComPtr<ID3D10Device1> device;
};

bool Device::Pimpl::Create(){
	static const D3D10_FEATURE_LEVEL1 levelAttempts[] = {
		D3D10_FEATURE_LEVEL_10_0,
		D3D10_FEATURE_LEVEL_10_1,
		D3D10_FEATURE_LEVEL_9_3,
		D3D10_FEATURE_LEVEL_9_2,
		D3D10_FEATURE_LEVEL_9_1,
	};

#ifdef _DEBUG
	CComPtr<IDXGIAdapter> selectedAdapter;
	CComPtr<IDXGIAdapter> adapter;
	D3D10_DRIVER_TYPE driverType = D3D10_DRIVER_TYPE_HARDWARE;
	UINT nAdapter = 0;
	CComPtr<IDXGIFactory> factory;
	HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory),(void**)&factory);
	if(FAILED(hr)){
		return false;
	}

	while(factory->EnumAdapters(nAdapter,&adapter)!=DXGI_ERROR_NOT_FOUND){
		if(adapter){
			DXGI_ADAPTER_DESC adaptDesc;
			if(SUCCEEDED(adapter->GetDesc(&adaptDesc))){
				const bool isPerfHUD = wcscmp(adaptDesc.Description, L"NVIDIA PerfHUD") == 0;
				if(nAdapter == 0 || isPerfHUD){
					selectedAdapter = adapter;
				}

				if(isPerfHUD){
					driverType = D3D10_DRIVER_TYPE_REFERENCE;
					break;
				}
			}
		}
		++nAdapter;
		adapter.Release();
	}

	CComPtr<ID3D10Device1> device1;
	UINT level = 0;
	for (; level < ARRAYSIZE(levelAttempts); ++level){
		if(SUCCEEDED(D3D10CreateDevice1( selectedAdapter, driverType, NULL, D3D10_CREATE_DEVICE_BGRA_SUPPORT, levelAttempts[level], D3D10_1_SDK_VERSION, &device1))){
			break;
		}
	}
	
#else
	CComPtr<ID3D10Device1> device1;
	UINT level = 0;
	for (; level < ARRAYSIZE(levelAttempts); ++level){
		if(SUCCEEDED(D3D10CreateDevice1( NULL, D3D10_DRIVER_TYPE_HARDWARE, NULL, D3D10_CREATE_DEVICE_BGRA_SUPPORT, levelAttempts[level],D3D10_1_SDK_VERSION, &device1))){
				break;
		}
	}
#endif

	if(level == ARRAYSIZE(levelAttempts)){
		MessageBox(NULL,L"機能レベルが対応してない？",L"error",MB_OK);
		return false;
	}
	
	if( FAILED( device1->QueryInterface(&device))){
		MessageBox(NULL,L"デバイスの取得に失敗",L"error",MB_OK);
		return false;
	}

	return true;
}

bool Device::Create(){
	pimpl.reset(new Pimpl);
	if(pimpl->Create()){
		SwapChain::Create(pimpl->device);
		return true;
	}
	return false;
}

CComPtr<ID3D10Device1> Device::GetDevice(){
	return pimpl->device;
}

void Device::Release(){
	SwapChain::Release();
	pimpl.reset();
}