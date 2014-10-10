#include "System/D3DCore.h"
#include "Graphic/BlendState/BlendState.h"
#include <atlbase.h>

using namespace Graphic;

class BlendState::Pimpl{
public:
	Pimpl(ID3D10Device* _device):device(_device){}

	static Pimpl* GetInstance(){
		static Pimpl pimpl(D3DCore::GetD3DDevice());
		return &pimpl;
	}

	HRESULT CreateState(D3D10_BLEND srcBlend, D3D10_BLEND destBlend, ID3D10BlendState** dst);

	CComPtr<ID3D10BlendState> add;
	CComPtr<ID3D10BlendState> alphaBlend;
	CComPtr<ID3D10BlendState> multiple;
	CComPtr<ID3D10BlendState> normal;
	CComPtr<ID3D10BlendState> lenear;

private:
	ID3D10Device* device;
};

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

	return device->CreateBlendState(&desc,dst);
}

BlendState::BlendState():pimpl(Pimpl::GetInstance()){}

BlendState::~BlendState(){}

ID3D10BlendState* BlendState::Default()const{
	if(!pimpl->normal && FAILED(pimpl->CreateState(D3D10_BLEND_ONE,D3D10_BLEND_ZERO,&pimpl->normal))){
		return nullptr;
	}
	return pimpl->normal;
}

ID3D10BlendState* BlendState::AlphaBlend()const{
	if(!pimpl->alphaBlend && FAILED(pimpl->CreateState(D3D10_BLEND_ONE,D3D10_BLEND_INV_SRC_ALPHA,&pimpl->alphaBlend))){
		return nullptr;
	}
	return pimpl->alphaBlend;
}

ID3D10BlendState* BlendState::Add()const{
	if(!pimpl->add && FAILED(pimpl->CreateState(D3D10_BLEND_SRC_ALPHA,D3D10_BLEND_ONE,&pimpl->add))){
		return nullptr;
	}
	return pimpl->add;
}

ID3D10BlendState* BlendState::Lenear()const{
	if(!pimpl->lenear && FAILED(pimpl->CreateState(D3D10_BLEND_SRC_ALPHA,D3D10_BLEND_INV_SRC_ALPHA,&pimpl->lenear))){
		return nullptr;
	}
	return pimpl->lenear;
}

ID3D10BlendState* BlendState::Multiple()const{
	if(!pimpl->multiple && FAILED(pimpl->CreateState(D3D10_BLEND_ZERO,D3D10_BLEND_SRC_COLOR,&pimpl->multiple))){
		return nullptr;
	}
	return pimpl->multiple;
}

//ID3D10BlendState* BlendState::Subtract()const{
//	if(FAILED(pimpl->CreateState(D3D10_BLEND_SRC_ALPHA,D3D10_BLEND_ONE,&pimpl->subtract))){
//		return pimpl->subtract;
//	}
//}
