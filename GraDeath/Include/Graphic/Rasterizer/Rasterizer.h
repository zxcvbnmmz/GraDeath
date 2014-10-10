#ifndef _RASTERIZER_H__
#define _RASTERIZER_H__

struct ID3D10RasterizerState;

namespace Graphic{
class Rasterizer{
public:
	Rasterizer();

	ID3D10RasterizerState* CullNone()const;
	ID3D10RasterizerState* CullClockWise()const;
	ID3D10RasterizerState* CullCounterClockWise()const;
	ID3D10RasterizerState* WireFrame()const;

private:
	class Pimpl;
	Pimpl* pimpl;
};
}

#endif	// end of Rasterizer