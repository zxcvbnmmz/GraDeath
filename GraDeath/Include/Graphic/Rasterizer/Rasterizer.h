#ifndef _RASTERIZER_H__
#define _RASTERIZER_H__

struct ID3D10RasterizerState;

namespace Graphic{
namespace Rasterizer{
	void CullNone();
	void CullClockWise();
	void CullCounterClockWise();
	void WireFrame();
};
}

#endif	// end of Rasterizer