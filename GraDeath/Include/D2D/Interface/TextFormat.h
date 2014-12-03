#ifndef _TEXT_FORMAT_H__
#define _TEXT_FORMAT_H__

#include <DWrite.h>
#include "D2D/Interface/WriteFactory.h"
#include "D2D/Interface/TextLayout.h"
#include <atlbase.h>
#include "Pool/Ref.h"

namespace D2D{
	struct TextFormat : public Ref{
		static TextFormat* Create(LPCWSTR font, float fontsize){
			TextFormat* textFormat = new TextFormat;
			if (textFormat != nullptr){
				ObjectPoolManager::GetInstance()->GetCurrentPool()->Add(textFormat);
				if (SUCCEEDED(D2D::WriteFactory::Get()->CreateTextFormat(
					font,NULL,DWRITE_FONT_WEIGHT_NORMAL,DWRITE_FONT_STYLE_NORMAL,
					DWRITE_FONT_STRETCH_NORMAL,fontsize,L"ja-jp",&textFormat->format))){
					return textFormat;
				}
			}
			return nullptr;
		}

		TextLayout* CreateLayout(float width, float height, size_t length, const wchar_t* str){
			TextLayout* textLayout = new TextLayout;
			if (textLayout != nullptr){
				ObjectPoolManager::GetInstance()->GetCurrentPool()->Add(textLayout);
				if (FAILED(D2D::WriteFactory::Get()->CreateTextLayout(
					str, length, format, width, height, &textLayout->layout))){
					textLayout->layout = nullptr;
				}

				return textLayout;
			}
			return nullptr;
		}

		friend struct TextObject;
	private:
		CComPtr<IDWriteTextFormat> format;
	};
}

#endif	// end of D2DFont