#ifndef _RASTERIZER_H__
#define _RASTERIZER_H__

struct ID3D10RasterizerState;

namespace Graphic{
namespace Rasterizer{
	ID3D10RasterizerState* CullNone();
	ID3D10RasterizerState* CullClockWise();
	ID3D10RasterizerState* CullCounterClockWise();
	ID3D10RasterizerState* WireFrame();
};
}

#endif	// end of Rasterizer