// ************************************************************
// fliename	FileUtility.cpp
// brief	�t�H���_���̃t�@�C�����̎擾
// name		����@�T
// memo
// 2013.08.20
// ************************************************************

// �C���N���[�h ***********************************************
#include "Scene/CaptureScene/FileUtility.h"
#include "Scene/CaptureScene/ConvertChar.h"


// �t�H���_���̃t�@�C�����̎擾
std::vector< std::string > ReadDirFileName(std::string folder)
{
	// �錾
	std::vector< std::string > fileList;
	HANDLE hFind;
	WIN32_FIND_DATA fd;

	// �t�@�C���������̂��߂Ƀ��C���h�J�[�h�ǉ�
	// �� : "D:\\Users\\Pictures\\*.*"
	std::stringstream ss;
	ss << folder;
	std::string::iterator itr = folder.end();
	itr--;
	if (*itr != '\\') ss << '\\';
	ss << "*.*";

	wchar_t path[MAX_PATH] = { 0 };
	// ���p�t�H���_�̏ꍇ����Ȃ��Ȃ�̂�1���Z
	ConvertWChar(ss.str().c_str(), ss.str().size() + 1, path);
	hFind = FindFirstFile(path, &fd);

	// �������s
	if (hFind == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, L"�t�@�C�����̎擾�Ɏ��s���܂���", L"error", MB_OK);
		fileList.clear();
		return fileList;//exit(1); // �G���[�I��
	}

	// �t�@�C���������X�g�Ɋi�[���邽�߂̃��[�v
	do
	{
		// �t�H���_�͏���
		if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
			!(fd.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN))
		{
			//�t�@�C���������X�g�Ɋi�[
			char file[256] = { 0 };// = fd.cFileName;
			ConvertChar(fd.cFileName, ss.str().size(), file);
			std::string str = file;
			fileList.push_back(str);
		}
	} while (FindNextFile(hFind, &fd)); //���̃t�@�C����T��

	// hFind�̃N���[�Y
	FindClose(hFind);

	return fileList;
}
