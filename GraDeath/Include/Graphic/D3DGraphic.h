#ifndef _D3D_GRAPHIC_H__
#define _D3D_GRAPHIC_H__

#include <D3D10_1.h>

namespace Graphic{
	namespace D3D{
		namespace VS{	// Vertex Shader
			void SetSampler(unsigned slot, unsigned numSamper, ID3D10SamplerState* sampler);
			void SetShaderResource(unsigned slot, unsigned numView, ID3D10ShaderResourceView*const* resource);
			void SetShader(ID3D10VertexShader* shader);
			void SetConstantBuffer(unsigned slot, unsigned numBuffer, ID3D10Buffer*const* buffer);
		};

		namespace PS{	// Pixel Shader
			void SetSampler(unsigned slot, unsigned numSampler, ID3D10SamplerState* sampler);
			void SetShaderResource(unsigned slot, unsigned numView, ID3D10ShaderResourceView*const* resource);
			void SetShader(ID3D10PixelShader* shader);
			void SetConstantBuffer(unsigned slot, unsigned numBuffer, ID3D10Buffer*const* buffer);
		};

		namespace IA{	// Input Assembler
			void SetLayout(ID3D10InputLayout* layout);
			void SetIndexBuffer(ID3D10Buffer* buffer, DXGI_FORMAT format, unsigned offset);
			void SetVertexBuffer(unsigned slot, unsigned numBuffer, ID3D10Buffer*const* buffer, unsigned stride, unsigned offset);
			void SetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY topology = D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		};

		namespace GS{	// Geometry Shader
			void SetSampler(unsigned slot, unsigned numSampler, ID3D10SamplerState*const* sampler);
			void SetShaderResource(unsigned slot, unsigned numView, ID3D10ShaderResourceView*const* resource);
			void SetShader(ID3D10GeometryShader* shader);
			void SetConstantBuffer(unsigned slot, unsigned numBuffer, ID3D10Buffer*const* buffer);
		};

		namespace OM{	// Output Merger
			HRESULT SetBlendMode(ID3D10BlendState*(*blendFunc)(void));
			HRESULT SetBlendMode(ID3D10BlendState* state);
			void SetDepthStencil(ID3D10DepthStencilState* state);
		};

		namespace RS{	// Rasterize Stage
			HRESULT SetRasterizeState(ID3D10RasterizerState* state);
			void SetViewport(unsigned int width, unsigned int height);
		};

		void Draw(unsigned numIndex, unsigned startIndexLocation);
		void Draw(unsigned numIndex, unsigned startIndexLocation, int baseVertexLocation);
		void ClearDepthStencilView(unsigned int clear = 0);
		HRESULT CreateShaderResourceView(ID3D10ShaderResourceView** texture, LPCWSTR fileName);


		namespace CS{	// Compute Shader
		}
		namespace SO{	// Stream Output
		}
		namespace HS{	// Hull Shader
		}
		namespace DS{	// Domain Shader
		}

	};
}

#endif	// end of D3DGraphic