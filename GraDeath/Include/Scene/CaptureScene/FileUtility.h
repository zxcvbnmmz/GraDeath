// ************************************************************
// fliename	FileUtility.h
// brief	�t�H���_���̃t�@�C�����̎擾
// name		����@�T
// memo
// 2013.08.20
// ************************************************************

// ���d�C���N���[�h�h�~ ***************************************
#ifndef	_READDIRFILENAME_H_
#define	_READDIRFILENAME_H_

// �C���N���[�h ***********************************************
#include <string>
#include <sstream>
#include <vector>
#include <Windows.h>


// ************************************************************
// �t�H���_���̃t�@�C�����̎擾
//
// variable
// std::string		: folder			: �t�H���_��
//
// return
// std::vector< std::string >			: �t�@�C�����̔z��
// ************************************************************
extern std::vector< std::string > ReadDirFileName(std::string folder);

#endif