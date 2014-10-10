#include "System/D3DCore.h"
#include "D3D/Device/Device.h"
#include <atlbase.h>

#include "D3D/SwapChain/SwapChain.h"

namespace D3DCore{
	namespace{
		ID3D10Device1* device;
		CComPtr<ID3D10RenderTargetView> renderTargetView;
		CComPtr<ID3D10DepthStencilView> depthStencilView;
		CComPtr<ID3D10Texture2D> depthStencil;
	}
}

void D3DCore::Destroy(){
	depthStencilView.Release();
	depthStencil.Release();
	renderTargetView.Release();

	D3D::Device::Release();
}

HRESULT D3DCore::Init(HWND _hwnd, int width, int height){
	if (D3D::Device::Create() == false){
		return E_FAIL;
	}
	//D3D::SwapChain::Create();
	device = D3D::Device::GetDevice();


	ID3D10Texture2D* pBackBuffer;
	D3D::SwapChain::GetBuffer(0, __uuidof(ID3D10Texture2D), (LPVOID*)&pBackBuffer);

	if (FAILED(device->CreateRenderTargetView(pBackBuffer, NULL, &renderTargetView.p))){
		return false;
	}

	pBackBuffer->Release();

	D3D10_TEXTURE2D_DESC descDepth;
	descDepth.Width = width;
	descDepth.Height = height;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D10_USAGE_DEFAULT;
	descDepth.BindFlags = D3D10_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	D3D::Device::GetDevice()->CreateTexture2D(&descDepth, NULL, &depthStencil);

	D3D10_DEPTH_STENCIL_VIEW_DESC descDSV;
	descDSV.Format = descDepth.Format;
	descDSV.ViewDimension = D3D10_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0;

	if (FAILED(device->CreateDepthStencilView(depthStencil, &descDSV, &depthStencilView))){
		return false;
	}

	device->OMSetRenderTargets(1, &(renderTargetView.p), depthStencilView);

	return S_OK;
}

void D3DCore::Draw(unsigned numIndex, unsigned startIndexLocation){
	device->Draw(numIndex, startIndexLocation);
}

void D3DCore::Draw(unsigned numIndex, unsigned startIndexLocation, int baseVertexLocation){
	device->DrawIndexed(numIndex, startIndexLocation, baseVertexLocation);
}

HRESULT D3DCore::Clear(float* clearColor, unsigned int clearFlag){
	device->ClearRenderTargetView(renderTargetView, clearColor);
	device->ClearDepthStencilView(depthStencilView, clearFlag, 1.0f, 0);
	return S_OK;
}

HRESULT D3DCore::ClearStencil(){
	device->ClearDepthStencilView(depthStencilView, D3D10_CLEAR_DEPTH, 1.0f, 0);
	return S_OK;
}

void D3DCore::SetDefaultRenderTarget(){
	device->OMSetRenderTargets(1, &renderTargetView, depthStencilView);
}

ID3D10Device1* D3DCore::GetD3DDevice(){
	return device;
}
