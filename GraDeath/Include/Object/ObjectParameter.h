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

struct CollisionParameter
{
	int	collisionModel;
	int	collisionType;
	int	strength;
	int		left;
	int		top;
	unsigned int	right;	// �l�p�Ȃ牡���A�~�Ȃ甼�a
	unsigned int	bottom; // �l�p�Ȃ�c���A�~�Ȃ�0

	CollisionParameter (){}
};

// �A�j���[�V����
struct AnimetionParameter
{
	int	annimaType;
	int	animaCount;
	int	effectCount;
	std::shared_ptr<char> effectFile;
	int	soundCount;
	std::shared_ptr<char> soudnFile;
	int	shortformCount;

	D3DXVECTOR2 size;

	std::vector<CollisionParameter*> collisionParameter;

	AnimetionParameter (){}
};

struct ObjectParameter
{
	int count;
	std::shared_ptr<char> fileName;
	int widthLength;
	int heightLength;

	std::vector<AnimetionParameter*> animeParameter;

	ObjectParameter (){}
};


#endif