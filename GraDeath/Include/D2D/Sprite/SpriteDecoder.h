#ifndef _SPRITE_DECODER_H__
#define _SPRITE_DECODER_H__

#include <D3D10_1.h>

struct ID2D1Bitmap;

namespace D2D{
	bool CreateSprite(ID2D1Bitmap** _bitmap, LPCWSTR _fileName);
}

#endif	// end of SpriteDecoder