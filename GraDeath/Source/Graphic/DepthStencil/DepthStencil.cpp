#include "System/D3DCore.h"
#include "Graphic/DepthStencil/DepthStencil.h"
#include "Graphic/D3DGraphic.h"
#include <atlbase.h>

namespace Graphic{
	namespace DepthStencil{
		class Pimpl;
	}
}

using namespace Graphic;

class DepthStencil::Pimpl{
public:
	Pimpl(){}

	HRESULT CreateState(bool enable, bool writeEnable, ID3D10DepthStencilState** dst);

	CComPtr<ID3D10DepthStencilState> depthNone;
	CComPtr<ID3D10DepthStencilState> depthDefault;
	CComPtr<ID3D10DepthStencilState> depthRead;
};

namespace {
	DepthStencil::Pimpl pimpl;
}

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

	return D3DCore::GetD3DDevice()->CreateDepthStencilState(&desc,dst);
}

void DepthStencil::DepthNone(){
	if(!pimpl.depthNone && FAILED(pimpl.CreateState(false,false,&pimpl.depthNone))){
		return ;
	}
	Graphic::D3D::OM::SetDepthStencil(pimpl.depthNone);
}

void DepthStencil::DepthDefault(){
	if(!pimpl.depthDefault && FAILED(pimpl.CreateState(true,true,&pimpl.depthDefault))){
		return ;
	}
	Graphic::D3D::OM::SetDepthStencil(pimpl.depthDefault);
}

void DepthStencil::DepthRead(){
	if(!pimpl.depthRead && FAILED(pimpl.CreateState(true,false,&pimpl.depthRead))){
		return ;
	}
	Graphic::D3D::OM::SetDepthStencil(pimpl.depthRead);
}

