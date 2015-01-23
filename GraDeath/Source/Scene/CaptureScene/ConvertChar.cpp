// ************************************************************
// fliename	ConvertChar.h
// brief	������̕ϊ�
// name		����@�T
// memo
// 2013.08.20
// ************************************************************

// �C���N���[�h ***********************************************
#include "Scene/CaptureScene/ConvertChar.h"
#include <stdlib.h>


// ���C�h������(WCHAR*)���}���`�o�C�g������(char*)�ɕϊ�
size_t ConvertWChar(const char* in_name, size_t size, wchar_t* out_name)
{
	size_t len = 0;
	setlocale(LC_ALL, "japanese");
	mbstowcs_s(&len, out_name, size, in_name, _TRUNCATE);

	return len;
}

// �}���`�o�C�g������(char*)�����C�h������(WCHAR*)�ɕϊ�
size_t ConvertChar(const wchar_t* in_name, size_t size, char* out_name)
{
	size_t len = 0;
	setlocale(LC_ALL, "japanese");
	wcstombs_s(&len, out_name, size, in_name, _TRUNCATE);

	return len;
}