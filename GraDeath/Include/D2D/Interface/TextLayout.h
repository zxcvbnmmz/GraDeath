#ifndef _TEXT_LAYOUT_H__
#define _TEXT_LAYOUT_H__

#include <DWrite.h>
#include "D2D/Interface/WriteFactory.h"
#include <atlbase.h>
#include "Pool/Ref.h"

namespace D2D{
	struct TextLayout : public Ref{
		TextLayout() :layout(nullptr){}
		friend struct TextFormat;
		friend struct TextObject;
	private:
		CComPtr<IDWriteTextLayout> layout;
	};

}
#endif	// endof D2DLayout