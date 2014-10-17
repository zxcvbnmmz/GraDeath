#include "System/D3DCore.h"
#include "Graphic/Sampler/Sampler.h"
#include "Graphic/D3DGraphic.h"
#include <atlbase.h>
#include <float.h>

namespace Sampler{
	class Pimpl;
}

class Sampler::Pimpl{
public:
	Pimpl(){}

	HRESULT CreateState(D3D10_FILTER filter, D3D10_TEXTURE_ADDRESS_MODE addressMode, ID3D10SamplerState** dst);

	CComPtr<ID3D10SamplerState> pointWrap;
	CComPtr<ID3D10SamplerState> pointClamp;
	CComPtr<ID3D10SamplerState> linearWrap;
	CComPtr<ID3D10SamplerState> linearClamp;
	CComPtr<ID3D10SamplerState> anisotropicWrap;
	CComPtr<ID3D10SamplerState> anisotropicClamp;
};

namespace {
	Sampler::Pimpl pimpl;
};

HRESULT Sampler::Pimpl::CreateState(D3D10_FILTER filter, D3D10_TEXTURE_ADDRESS_MODE addressMode, ID3D10SamplerState** dst){
	D3D10_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));

	desc.AddressU = addressMode;
	desc.AddressV = addressMode;
	desc.AddressW = addressMode;

	desc.MaxAnisotropy = (D3DCore::GetD3DDevice()->GetFeatureLevel() > D3D_FEATURE_LEVEL_9_1) ? 16 : 2;
	desc.MaxLOD = FLT_MAX;
	desc.ComparisonFunc = D3D10_COMPARISON_NEVER;

	return D3DCore::GetD3DDevice()->CreateSamplerState(&desc, dst);
}

void Sampler::SetPointWrap(unsigned int slot){
	if (!pimpl.pointWrap && FAILED(pimpl.CreateState(D3D10_FILTER_MIN_MAG_MIP_POINT, D3D10_TEXTURE_ADDRESS_WRAP, &pimpl.pointWrap))){
		return;
	}

	Graphic::D3D::PS::SetSampler(slot, 1, pimpl.pointWrap);
}

void Sampler::SetPointClamp(unsigned int slot){
	if (!pimpl.pointClamp && FAILED(pimpl.CreateState(D3D10_FILTER_MIN_MAG_MIP_POINT, D3D10_TEXTURE_ADDRESS_CLAMP, &pimpl.pointClamp))){
		return;
	}
	Graphic::D3D::PS::SetSampler(slot, 1, pimpl.pointClamp);
}

void Sampler::SetLinearWrap(unsigned int slot){
	if (!pimpl.linearWrap && FAILED(pimpl.CreateState(D3D10_FILTER_MIN_MAG_MIP_LINEAR, D3D10_TEXTURE_ADDRESS_WRAP, &pimpl.linearWrap))){
		return;
	}
	Graphic::D3D::PS::SetSampler(slot, 1, pimpl.linearWrap);
}

void Sampler::SetLinearClamp(unsigned int slot){
	if (!pimpl.linearClamp && FAILED(pimpl.CreateState(D3D10_FILTER_MIN_MAG_MIP_LINEAR, D3D10_TEXTURE_ADDRESS_WRAP, &pimpl.linearClamp))){
		return;
	}
	Graphic::D3D::PS::SetSampler(slot, 1, pimpl.linearClamp);
}

void Sampler::SetAnisotropicWrap(unsigned int slot){
	//if(!pimpl.anisotropicWrap && FAILED(pimpl.CreateState(D3D10_FILTER_MIN_MAG_MIP_POINT, D3D10_TEXTURE_ADDRESS_WRAP, &pimpl.anisotropicWrap))){
	//return nullptr;
	//}
}

void Sampler::SetAnisotropicClamp(unsigned int slot){
	//if(!pimpl.anisotropicClamp && FAILED(pimpl.CreateState(D3D10_FILTER_MIN_MAG_MIP_POINT, D3D10_TEXTURE_ADDRESS_WRAP, &pimpl.anisotropicClamp))){
	//return nullptr;
	//}
}
