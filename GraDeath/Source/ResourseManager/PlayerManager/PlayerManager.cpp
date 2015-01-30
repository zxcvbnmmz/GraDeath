// ************************************************************
// filename	PlayerManager.cpp
// brief	Player�̊Ǘ�
// name		����@�T
// note
// 2014.10.27
// ************************************************************

// �C���N���[�h ***********************************************
#include "ResourseManager/PlayerManager/PlayerManager.h"
#include "Object/Character.h"
#include "Utility/SafeDelete.h"
#include "CharacterController/CharacterController.h"
#include <vector>


#define CONTROLLER_SIZE ( 3 )

namespace PlayerManager
{
	namespace
	{
		std::vector< CharacterController* > controller;
	}

	// ������
	void Init ()
	{
		Release ();
		controller.resize ( CONTROLLER_SIZE );
		for ( int i = 0; i < CONTROLLER_SIZE; i++ )
			controller[ i ] = nullptr;
	}

	// �X�V
	void Update ()
	{
		for ( int i = 0; i < CONTROLLER_SIZE; i++ )
		{
			if ( controller[ i ] == nullptr )
				controller[ i ]->Update ();
		}
	}

	// �`��
	void Draw ()
	{
		for ( int i = 0; i < CONTROLLER_SIZE; i++ )
		{
			if ( controller[ i ] == nullptr )
				controller[ i ]->Draw ();
		}
	}

	// ���
	void Release ()
	{
		for ( int i = 0; i < CONTROLLER_SIZE; i++ )
		{
			Util::safeDelete ( controller[ i ] );
		}
		controller.clear ();
	}

	// �R���g���[���[�Z�b�g
	void SetController ( CharacterController* _controller )
	{
		controller.push_back ( _controller );
	}

}
