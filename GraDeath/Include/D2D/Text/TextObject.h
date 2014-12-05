#ifndef _TEXT_H__
#define _TEXT_H__

#include <string>
#include <atlbase.h>
#include "D2D/Interface/TextLayout.h"
#include "D2D/Interface/TextFormat.h"

class Brush;

namespace D2D{
	struct TextObject{
	public:
		void DrawString(float x, float y, const wchar_t* str, ...);
		void DrawLayout(float x, float y);
		struct TextFormat* format;
		struct TextLayout* layout;
		Brush* brush;
	};
}

#endif	// end of Text