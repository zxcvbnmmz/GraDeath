#include "Graphic/D3DGraphic.h"
#include "System/D3DCore.h"
#include <D3DX10.h>
#include <atlbase.h>

namespace Graphic{
	namespace {
		CComQIPtr<ID3D10DepthStencilView> stencilView;
	}

	namespace D3D{
		// Vertex Shader
		void VS::SetSampler(unsigned slot, unsigned numSampler, ID3D10SamplerState* sampler){
			D3DCore::GetD3DDevice()->VSSetSamplers(slot,numSampler,&sampler);
		}

		void VS::SetShaderResource(unsigned slot, unsigned numView, ID3D10ShaderResourceView*const* resource){
			D3DCore::GetD3DDevice()->VSSetShaderResources(slot,numView,resource);
		}

		void VS::SetShader(ID3D10VertexShader* shader){
			D3DCore::GetD3DDevice()->VSSetShader(shader);
		}
			
		void VS::SetConstantBuffer(unsigned slot, unsigned numBuffer, ID3D10Buffer*const* buffer){
			D3DCore::GetD3DDevice()->VSSetConstantBuffers(slot,numBuffer,buffer);
		}

		// Pixel Shader
		void PS::SetSampler(unsigned slot, unsigned numSampler, ID3D10SamplerState* sampler){
			D3DCore::GetD3DDevice()->PSSetSamplers(slot,numSampler,&sampler);
		}

		void PS::SetShaderResource(unsigned slot, unsigned numView, ID3D10ShaderResourceView*const* resource){
			D3DCore::GetD3DDevice()->PSSetShaderResources(slot,numView,resource);
		}
			
		void PS::SetShader(ID3D10PixelShader* shader){
			D3DCore::GetD3DDevice()->PSSetShader(shader);
		}
			
		void PS::SetConstantBuffer(unsigned slot, unsigned numBuffer, ID3D10Buffer*const* buffer){
			D3DCore::GetD3DDevice()->PSSetConstantBuffers(slot,numBuffer,buffer);
		}

		// Input Assembler
		void IA::SetLayout(ID3D10InputLayout* layout){
			D3DCore::GetD3DDevice()->IASetInputLayout(layout);
		}

		void IA::SetIndexBuffer(ID3D10Buffer* buffer, DXGI_FORMAT format, unsigned offset){
			D3DCore::GetD3DDevice()->IASetIndexBuffer(buffer,format,offset);
		}
		
		void IA::SetVertexBuffer(unsigned slot, unsigned numBuffer, ID3D10Buffer*const* buffer, unsigned stride, unsigned offset){
			D3DCore::GetD3DDevice()->IASetVertexBuffers(slot,numBuffer,buffer, &stride, &offset);
		}
		
		void IA::SetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY topology){
			D3DCore::GetD3DDevice()->IASetPrimitiveTopology(topology);
		}
		
		void Draw(unsigned numVertex, unsigned startVertexLocation){
			D3DCore::Draw(numVertex,startVertexLocation);
		}

		void Draw(unsigned numIndex, unsigned startIndexLocation, int baseVertexLocation){
			D3DCore::Draw(numIndex,startIndexLocation,baseVertexLocation);
		}

		HRESULT OM::SetBlendMode(ID3D10BlendState*(*blendFunc)(void)){
			UINT mask = 0xffffffff;

			ID3D10BlendState* state = blendFunc();
			if(!state){
				return E_FAIL;
			}

			D3DCore::GetD3DDevice()->OMSetBlendState(state, 0, mask);
			return S_OK;
		}

		HRESULT OM::SetBlendMode(ID3D10BlendState* state){
			if(!state){
				return E_FAIL;
			}

			UINT mask = 0xffffffff;
			D3DCore::GetD3DDevice()->OMSetBlendState(state, 0, mask);
			return S_OK;
		}

		void OM::SetDepthStencil(ID3D10DepthStencilState* state){
			D3DCore::GetD3DDevice()->OMSetDepthStencilState(state,1);
		}

		HRESULT RS::SetRasterizeState(ID3D10RasterizerState* rasterizer){
			if(!rasterizer){
				return E_FAIL;
			}

			D3DCore::GetD3DDevice()->RSSetState(rasterizer);
			return S_OK;
		}

		void RS::SetViewport(unsigned int width, unsigned int height){
			D3D10_VIEWPORT vp = {0,0,width,height,0.0f,1.0f};
			D3DCore::GetD3DDevice()->RSSetViewports(1,&vp);
		}

		void ClearDepthStencilView(unsigned int clear){
			D3DCore::GetD3DDevice()->ClearDepthStencilView(stencilView,D3D10_CLEAR_DEPTH|D3D10_CLEAR_STENCIL,1.0f,clear);
		}

		HRESULT CreateShaderResourceView(ID3D10ShaderResourceView** texture, LPCWSTR fileName){
			return D3DX10CreateShaderResourceViewFromFile(D3DCore::GetD3DDevice(),fileName,NULL,NULL,texture,NULL);
		}
	};
};
