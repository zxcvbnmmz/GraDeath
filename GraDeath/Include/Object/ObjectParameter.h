#ifndef _OBJECT_PARAMETER_H_
#define _OBJECT_PARAMETER_H_

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
	char*	effectFile;
	int	soundCount;
	char*	soudnFile;
	int	shortformCount;
	CollisionParameter* collisionParameter;

	AnimetionParameter (){}
};

struct ObjectParameter
{
	int count;
	char* fileName;
	int widthLength;
	int heightLength;
	AnimetionParameter* animeParameter;

	ObjectParameter (){}
};


#endif	// end of CharacterLoader