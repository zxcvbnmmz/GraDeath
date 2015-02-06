#include "D3D/SwapChain/SwapChain.h"
#include <D3D10_1.h>
#include "System/Window.h"

using namespace D3D;

namespace {
	IDXGISwapChain* swapChain;
}

bool SwapChain::Create(CComPtr<ID3D10Device1> _device){
	if(swapChain){
		return true;
	}

	CComQIPtr<IDXGIDevice> giDevice;
	if( FAILED( _device->QueryInterface(&giDevice))){
		MessageBox(NULL,L"IDXGIDevice‚ÌŽæ“¾‚ÉŽ¸”s",L"",MB_OK);
		return false;
	}
	
	CComQIPtr<IDXGIAdapter> giAdapter;
	if( FAILED( giDevice->GetAdapter(&giAdapter))){
		MessageBox(NULL,L"IDXAdapter‚ÌŽæ“¾‚ÉŽ¸”s",L"",MB_OK);
		return false;
	}

	CComQIPtr<IDXGIFactory> giFactory;
    if( FAILED( giAdapter->GetParent(IID_PPV_ARGS(&giFactory)))){
		MessageBox(NULL,L"IDXFactory‚ÌŽæ“¾‚ÉŽ¸”s",L"",MB_OK);
		return false;
	}

	int width,height;
	System::Window::GetWindowSize(&width,&height);
	HWND hwnd;
	System::Window::GetHWND(&hwnd);

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = width;
	sd.BufferDesc.Height = height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hwnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;


	if( FAILED( giFactory->CreateSwapChain(giDevice, &sd, &swapChain))){
		MessageBox(NULL,L"SwapChain‚Ìì¬‚ÉŽ¸”s",L"",MB_OK);
		return false;
	}

	return true;
}

bool SwapChain::GetBuffer(unsigned int buffer, const IID& riid, void** surface){
	if(FAILED(swapChain->GetBuffer(buffer,riid, surface))){
		return false;
	}
	return true;
}

void SwapChain::Present(UINT syncInterval, UINT flag){
	swapChain->Present(syncInterval, flag);
}

void SwapChain::GetDesc(DXGI_SWAP_CHAIN_DESC* _desc){
	swapChain->GetDesc(_desc);
}

void SwapChain::Release(){
	if(swapChain){
		swapChain->Release();
		swapChain = nullptr;
	}
}

IDXGISwapChain* SwapChain::GetSwapChain(){
	return swapChain;
}