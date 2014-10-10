#include "Graphic/RenderTarget/RenderTarget.h"
#include "System/D3DCore.h"
#include "Graphic/D3DGraphic.h"

using namespace Graphic;

RenderTarget::RenderTarget():device(D3DCore::GetD3DDevice()){
	clearColor[0] = 1;
	clearColor[1] = 1;
	clearColor[2] = 1;
	clearColor[3] = 1;
}

bool RenderTarget::Initialize(unsigned int width, unsigned int height){
	D3D10_TEXTURE2D_DESC textureDesc;
	ZeroMemory(&textureDesc,sizeof(textureDesc));

	textureDesc.Width = width;
	textureDesc.Height = height;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	textureDesc.SampleDesc.Count = 1;
	textureDesc.Usage = D3D10_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D10_BIND_RENDER_TARGET | D3D10_BIND_SHADER_RESOURCE;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;

	if(FAILED(device->CreateTexture2D(&textureDesc,NULL,&renderTarget))){
		return false;
	}
	
	D3D10_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
	renderTargetViewDesc.Format = textureDesc.Format;
	renderTargetViewDesc.ViewDimension = D3D10_RTV_DIMENSION_TEXTURE2D;
	renderTargetViewDesc.Texture2D.MipSlice = 0;

	if(FAILED(device->CreateRenderTargetView(renderTarget,&renderTargetViewDesc, &renderTargetView))){
		return false;
	}

	D3D10_SHADER_RESOURCE_VIEW_DESC resourceDesc;
	resourceDesc.Format = textureDesc.Format;
	resourceDesc.ViewDimension = D3D10_SRV_DIMENSION_TEXTURE2D;
	resourceDesc.Texture2D.MostDetailedMip = 0;
	resourceDesc.Texture2D.MipLevels = 1;

	if(FAILED(device->CreateShaderResourceView(renderTarget,&resourceDesc,&texture))){
		return false;
	}

	D3D10_TEXTURE2D_DESC depthStencilDesc;
	depthStencilDesc.Width = width;
	depthStencilDesc.Height = height;
	depthStencilDesc.MipLevels = 1;
	depthStencilDesc.ArraySize = 1;
	depthStencilDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDesc.SampleDesc.Count = 1;
	depthStencilDesc.SampleDesc.Quality = 0;
	depthStencilDesc.Usage = D3D10_USAGE_DEFAULT;
	depthStencilDesc.BindFlags = D3D10_BIND_DEPTH_STENCIL;
	depthStencilDesc.CPUAccessFlags = 0;
	depthStencilDesc.MiscFlags = 0;
	
	if(FAILED(device->CreateTexture2D(&depthStencilDesc,NULL,&depthStencil))){
		return false;
	}

	D3D10_DEPTH_STENCIL_VIEW_DESC stencilViewDesc;
	stencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	stencilViewDesc.ViewDimension = D3D10_DSV_DIMENSION_TEXTURE2D;
	stencilViewDesc.Texture2D.MipSlice = 0;

	if(FAILED(device->CreateDepthStencilView(depthStencil,&stencilViewDesc,&depthStencilView))){
		return false;
	}

	return true;
}

void RenderTarget::SetClearColor(float r, float g, float b, float a){
	clearColor[0] = r;
	clearColor[1] = g;
	clearColor[2] = b;
	clearColor[3] = a;
}

void RenderTarget::Clear(CLEAR_FLAG flag){
	device->ClearRenderTargetView(renderTargetView,clearColor);
	device->ClearDepthStencilView(depthStencilView,flag,1.0f,0);
}

void RenderTarget::Begin(){
	device->OMGetRenderTargets(1,&currentRenderTarget.p,&currentStencilView.p);
	device->OMSetRenderTargets(1,&renderTargetView.p,depthStencilView.p);
}

void RenderTarget::End(){
	device->OMSetRenderTargets(1,&currentRenderTarget.p,currentStencilView.p);
	currentRenderTarget.Release();
	currentStencilView.Release();
}

void RenderTarget::GetResource(CComPtr<ID3D10ShaderResourceView>& dst){
	dst = texture;
}

void RenderTarget::SetToShader(unsigned int slot){
	Graphic::D3D::PS::SetShaderResource(slot,1,&texture.p);
}
