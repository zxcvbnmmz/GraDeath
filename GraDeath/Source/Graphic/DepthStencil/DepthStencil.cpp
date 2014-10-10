#include "System/D3DCore.h"
#include "Graphic/DepthStencil/DepthStencil.h"
#include <atlbase.h>

using namespace Graphic;

class DepthStencil::Pimpl{
public:
	Pimpl(ID3D10Device* _device):device(_device){}
	static Pimpl* GetInstance(){
		static Pimpl pimpl(D3DCore::GetD3DDevice());
		return &pimpl;
	}

	HRESULT CreateState(bool enable, bool writeEnable, ID3D10DepthStencilState** dst);

	CComPtr<ID3D10DepthStencilState> depthNone;
	CComPtr<ID3D10DepthStencilState> depthDefault;
	CComPtr<ID3D10DepthStencilState> depthRead;

private:
	ID3D10Device* device;
};

HRESULT DepthStencil::Pimpl::CreateState(bool enable, bool writeEnable, ID3D10DepthStencilState** dst){
	D3D10_DEPTH_STENCIL_DESC desc;
	ZeroMemory( &desc, sizeof(desc));

	desc.DepthEnable = enable;
	desc.DepthWriteMask = writeEnable ? D3D10_DEPTH_WRITE_MASK_ALL : D3D10_DEPTH_WRITE_MASK_ZERO;
	desc.DepthFunc = D3D10_COMPARISON_LESS_EQUAL;

	desc.StencilEnable = false;
	desc.StencilReadMask = D3D10_DEFAULT_STENCIL_READ_MASK;
	desc.StencilWriteMask = D3D10_DEFAULT_STENCIL_WRITE_MASK;

	desc.FrontFace.StencilFunc = D3D10_COMPARISON_ALWAYS;
	desc.FrontFace.StencilPassOp = D3D10_STENCIL_OP_KEEP;
	desc.FrontFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
	desc.FrontFace.StencilDepthFailOp = D3D10_STENCIL_OP_KEEP;

	desc.BackFace = desc.FrontFace;

	return device->CreateDepthStencilState(&desc,dst);
}

DepthStencil::DepthStencil():pimpl(Pimpl::GetInstance()){}

ID3D10DepthStencilState* DepthStencil::DepthNone()const{
	if(!pimpl->depthNone && FAILED(pimpl->CreateState(false,false,&pimpl->depthNone))){
		return nullptr;
	}
	return pimpl->depthNone;
}

ID3D10DepthStencilState* DepthStencil::DepthDefault()const{
	if(!pimpl->depthDefault && FAILED(pimpl->CreateState(true,true,&pimpl->depthDefault))){
		return nullptr;
	}
	return pimpl->depthDefault;
}

ID3D10DepthStencilState* DepthStencil::DepthRead()const{
	if(!pimpl->depthRead && FAILED(pimpl->CreateState(true,false,&pimpl->depthRead))){
		return nullptr;
	}
	return pimpl->depthRead;
}

