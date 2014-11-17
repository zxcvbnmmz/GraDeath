#ifndef _OBJECT_PARAMETER_H_
#define _OBJECT_PARAMETER_H_

#include <vector>
#include <D3DX10math.h>
#include <memory>

enum COLLISION_MODEL
{
	CUBE = 0,
	SPHERE = 1,
};

enum Type
{
	ATTACK = 0,
	DAMEGE = 1,
	ATTACK_AND_DAMEGE = 2,
	SUPER_ARMOR = 4,
};

// �`�f�[�^
struct ShapeData
{
	short	collisionModel;	// �����蔻��̌`(0=�����`:1=�~)
	short	collisionType;	// �����蔻��̎��(0=�U��:1=��:2=����:3=���G)
	short	strength;		// ����
	union {
		struct {
			int x[ 4 ];		// 0:���� 1:�E�� 2:�E�� 3:����
			int y[ 4 ];
		}square;
		struct {
			int x;			// ���S
			int y;
			int rad;		// ���a
		}circle;
	}shape;
};


// �A�j���[�V�����̃��[�v
struct CellData
{
	short	animUse;		// �Z�����g�p���邩���Ȃ���
	short	animType;		// �A�j���[�V�����^�C�v(0=����:1=�ړ�:2=�W�����v:3=�U��:4=��)
	short	animFrame;		// 1�R�}�ɕK�v�ȃt���[����
	//short	effectCount;	// �G�t�F�N�g���̕�����
	//char*	effectFile;		// �G�t�F�N�g��
	//short	soundCount;		// �T�E���h���̕�����
	//char*	soundFile;		// �T�E���h�t�@�C��
	short	shapeCount;		// �`��

	std::vector< std::shared_ptr< ShapeData > > shapeData;	// �`�f�[�^
};


struct AnimationData
{
	// ����HP�Ȃǂ̃f�[�^���i�[����\������(�،��F���c)
	char* fileName;
	D3DXVECTOR2 cellSize;		// �Z���̃T�C�Y
	int rectWCount;		// ������
	int rectHCount;		// ������
	std::vector< std::vector< std::shared_ptr< CellData > > > cellDatas;
};


#endif