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
	unsigned int	right;	// lŠp‚È‚ç‰¡•A‰~‚È‚ç”¼Œa
	unsigned int	bottom; // lŠp‚È‚çc•A‰~‚È‚ç0

	CollisionParameter (){}
};

// ƒAƒjƒ[ƒVƒ‡ƒ“
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