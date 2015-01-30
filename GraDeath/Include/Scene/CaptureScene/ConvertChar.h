// ************************************************************
// fliename	ConvertChar.h
// brief	������̕ϊ�
// name		����@�T
// memo
// 2013.08.20
// ************************************************************

// ���d�C���N���[�h�h�~ ***************************************
#ifndef	_CONVERT_CHAR_H_
#define	_CONVERT_CHAR_H_

// �C���N���[�h ***********************************************
#include <locale.h>


// ************************************************************
// ���C�h������(WCHAR*)���}���`�o�C�g������(char*)�ɕϊ�
//
// variable
// char*			: in_name			: �ϊ��O������
// size_t			: size				: ������̒���
// wchar_t*			: out_name			: �ϊ��㕶����
// ************************************************************
extern size_t ConvertWChar(const char* in_name, size_t size, wchar_t* out_name);

// ************************************************************
// �}���`�o�C�g������(char*)�����C�h������(WCHAR*)�ɕϊ�
//
// variable
// wchar_t*			: in_name			: �ϊ��O������
// size_t			: size				: ������̒���
// char*			: out_name			: �ϊ��㕶����
// ************************************************************
extern size_t ConvertChar(const wchar_t* in_name, size_t size, char* out_name);

#endif