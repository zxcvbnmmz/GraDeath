#ifndef _OBJECT_PARAMETER_H_
#define _OBJECT_PARAMETER_H_

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