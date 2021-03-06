#include "System/D3DCore.h"
#include "Graphic/BlendState/BlendState.h"
#include "Graphic/D3DGraphic.h"
#include <atlbase.h>

namespace Graphic{
	namespace BlendState{
		class Pimpl;
	}
}

using namespace Graphic;

class BlendState::Pimpl{
public:
	Pimpl(){}

	HRESULT CreateState(D3D10_BLEND srcBlend, D3D10_BLEND destBlend, ID3D10BlendState** dst);

	CComPtr<ID3D10BlendState> add;
	CComPtr<ID3D10BlendState> alphaBlend;
	CComPtr<ID3D10BlendState> multiple;
	CComPtr<ID3D10BlendState> normal;
	CComPtr<ID3D10BlendState> lenear;
};


namespace {
	BlendState::Pimpl pimpl;
}

HRESULT BlendState::Pimpl::CreateState(D3D10_BLEND srcBlend, D3D10_BLEND destBlend, ID3D10BlendState** dst){
	if(*dst != nullptr){
		return S_OK;
	}

	D3D10_BLEND_DESC desc;
	ZeroMemory( &desc, sizeof(desc));
	desc.BlendEnable[0]	= (srcBlend != D3D10_BLEND_ONE) || (destBlend != D3D10_BLEND_ZERO);
	desc.RenderTargetWriteMask[ 0 ]	= D3D10_COLOR_WRITE_ENABLE_ALL;
	desc.SrcBlend = desc.SrcBlendAlpha = srcBlend;
	desc.DestBlend = desc.DestBlendAlpha = destBlend;
	desc.BlendOp = desc.BlendOpAlpha = D3D10_BLEND_OP_ADD;

	return D3DCore::GetD3DDevice()->CreateBlendState(&desc,dst);
}

void BlendState::Default(){
	if(!pimpl.normal && FAILED(pimpl.CreateState(D3D10_BLEND_ONE,D3D10_BLEND_ZERO,&pimpl.normal))){
		return ;
	}
	Graphic::D3D::OM::SetBlendMode(pimpl.normal);
}

void BlendState::AlphaBlend(){
	if(!pimpl.alphaBlend && FAILED(pimpl.CreateState(D3D10_BLEND_ONE,D3D10_BLEND_INV_SRC_ALPHA,&pimpl.alphaBlend))){
		return ;
	}
	Graphic::D3D::OM::SetBlendMode(pimpl.alphaBlend);
}

void BlendState::Add(){
	if(!pimpl.add && FAILED(pimpl.CreateState(D3D10_BLEND_SRC_ALPHA,D3D10_BLEND_ONE,&pimpl.add))){
		return ;
	}
	Graphic::D3D::OM::SetBlendMode(pimpl.add);
}

void BlendState::Lenear(){
	if(!pimpl.lenear && FAILED(pimpl.CreateState(D3D10_BLEND_SRC_ALPHA,D3D10_BLEND_INV_SRC_ALPHA,&pimpl.lenear))){
		return ;
	}
	Graphic::D3D::OM::SetBlendMode(pimpl.lenear);
}

void BlendState::Multiple(){
	if(!pimpl.multiple && FAILED(pimpl.CreateState(D3D10_BLEND_ZERO,D3D10_BLEND_SRC_COLOR,&pimpl.multiple))){
		return ;
	}
	Graphic::D3D::OM::SetBlendMode(pimpl.multiple);
}

//ID3D10BlendState* BlendState::Subtract()const{
//	if(FAILED(pimpl.CreateState(D3D10_BLEND_SRC_ALPHA,D3D10_BLEND_ONE,&pimpl.subtract))){
//		return pimpl.subtract;
//	}
//}
