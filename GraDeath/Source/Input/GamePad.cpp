// ************************************************************
// filename	GamePad.h
// brief	XInput�̊֐���Z�߂����b�p�[
// name		����@�T
// note
// 2014.10.10
// ************************************************************

// �C���N���[�h ***********************************************
#include "Input/GamePad.h"
#include <windows.h>
#include <XInput.h>
#include <D3DX10math.h>
#include <math.h>


// �X�^�e�B�b�N���C�u�����̒ǉ�
#pragma comment (lib,"Xinput.lib")


// XInput�̔F���͍ő�4��
#define MAX_CONTROLLERS ( 4 )
// 臒l��MAX
#define INPUT_DEADZONE  ( 0.24f * float( 0x7FFF ) )

namespace GamePad
{
	// �p�b�h�̃f�b�g�]�[������
	void padDeadZone ( int );

	namespace
	{
		// ************************************************************
		// struct PadState
		// ************************************************************
		struct PadState
		{
			XINPUT_STATE	state;				// �X�e�[�^�X
			int				count[ 14 ];		// �J�E���g�̊i�[
			bool			isActive;			// �A�N�e�B�u
		};
		// Pad�̕ϐ�
		PadState	pad[ MAX_CONTROLLERS ];
		// �{�^���̉ߋ����
		DWORD		oldButtonsBuf[ MAX_CONTROLLERS ];
		// 臒l
		float		threshold;
		// DeadZone
		bool		deadZone;
	}

	// ������
	void init ()
	{
		ZeroMemory ( pad, sizeof( PadState )* MAX_CONTROLLERS );
		ZeroMemory ( oldButtonsBuf, sizeof( DWORD )* MAX_CONTROLLERS );
		threshold = 0.0f;
		deadZone = true;
	}

	// �X�V
	int update ()
	{
		DWORD _state = 0;
		for ( int i = 0; i < MAX_CONTROLLERS; i++ )
		{
			// �ߋ��֊i�[
			oldButtonsBuf[ i ] = pad[ i ].state.Gamepad.wButtons;

			_state = XInputGetState ( i, &pad[ i ].state );

			if ( _state == ERROR_SUCCESS )
			{
				padDeadZone ( i );
				pad[ i ].isActive = true;
			}
			else
			{
				pad[ i ].isActive = false;
			}
		}
		return 1;
	}

	// �p�b�h�̃f�b�g�]�[������
	void padDeadZone ( int _num )
	{
		if ( !deadZone )
			return;

		// �͈͂̐ݒ�
		if ( ( pad[ _num ].state.Gamepad.sThumbLX < threshold &&
			pad[ _num ].state.Gamepad.sThumbLX > -threshold ) &&
			( pad[ _num ].state.Gamepad.sThumbLY < threshold &&
			pad[ _num ].state.Gamepad.sThumbLY > -threshold ) )
		{
			pad[ _num ].state.Gamepad.sThumbLX = 0;
			pad[ _num ].state.Gamepad.sThumbLY = 0;
		}

		if ( ( pad[ _num ].state.Gamepad.sThumbRX < threshold &&
			pad[ _num ].state.Gamepad.sThumbRX > -threshold ) &&
			( pad[ _num ].state.Gamepad.sThumbRY < threshold &&
			pad[ _num ].state.Gamepad.sThumbRY > -threshold ) )
		{
			pad[ _num ].state.Gamepad.sThumbRX = 0;
			pad[ _num ].state.Gamepad.sThumbRY = 0;
		}
	}

	// 臒l�̐ݒ�
	void setThreshold ( float _threshold )
	{
		float tempThreshold = ( _threshold < 0.0f ) ? 0.0f : _threshold;
		tempThreshold = ( _threshold > 1.0f ) ? 1.0f : _threshold;

		D3DXVECTOR2 tempPos ( INPUT_DEADZONE, INPUT_DEADZONE );
		float tempLen = D3DXVec2Length ( &tempPos );

		threshold = tempLen * _threshold;
	}

	// �X�e�B�b�N�̃f�b�g�]�[���ݒ�
	void setStickDeadZone ( bool _flg )
	{
		deadZone = _flg;
	}

	// �Q�[���p�b�h�̏��擾
	INPUT_STATE getGamePadState(PAD_NUM _num, BUTTON_ID _button, int* _count)
	{
		if ( !pad[ _num ].isActive )
			return INPUT_FREE;

		DWORD button = ( pad[ _num ].state.Gamepad.wButtons & _button );
		DWORD oldButton = ( oldButtonsBuf[ _num ] & _button );

		if ( !button && !oldButton )
			return INPUT_FREE;
		if ( button && !oldButton )
			return INPUT_PUSH;
		if ( button &&   oldButton )
			return INPUT_PRESS;
		if ( !button &&   oldButton )
			return INPUT_RELEASE;

		return INPUT_FREE;
	}

	// �Q�[���p�b�h��LR�g���K�[���擾
	int getRTriggerState ( PAD_NUM _num, int* _trigger )
	{
		if ( _trigger != nullptr )
			*_trigger = static_cast< int >( pad[ _num ].state.Gamepad.bRightTrigger );

		return static_cast< int >( pad[ _num ].state.Gamepad.bRightTrigger );
	}

	int getLTriggerState ( PAD_NUM _num, int* _trigger )
	{
		if ( _trigger != nullptr )
			*_trigger = static_cast< int >( pad[ _num ].state.Gamepad.bLeftTrigger );

		return static_cast< int >( pad[ _num ].state.Gamepad.bLeftTrigger );
	}

	// �Q�[���p�b�h�̃X�e�B�b�N���擾
	bool getRStickState ( PAD_NUM _num, float& _angle )
	{
		D3DXVECTOR2 tempPos ( pad[ _num ].state.Gamepad.sThumbRX, pad[ _num ].state.Gamepad.sThumbRY );
		float tempLen = D3DXVec2Length ( &tempPos );

		_angle = atan2 ( tempPos.y, tempPos.x );

		return ( threshold < tempLen );
	}

	bool getLStickState ( PAD_NUM _num, float& _angle )
	{
		D3DXVECTOR2 tempPos ( pad[ _num ].state.Gamepad.sThumbLX, pad[ _num ].state.Gamepad.sThumbLY );
		float tempLen = D3DXVec2Length ( &tempPos );

		_angle = atan2 ( tempPos.y, tempPos.x );

		return ( threshold < tempLen );
	}

	bool getAnyGamePadPressed(BUTTON_ID _button){
		for (int i = 0; i < 4; ++i){
			if (!pad[i].isActive)
				continue;

			if ((pad[i].state.Gamepad.wButtons & _button) != 0){
				return true;
			}
		}
		return false;
	}
}
