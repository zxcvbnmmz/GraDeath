#ifndef _WHITE_BLACK_SECOND_SKILL_H_
#define _WHITE_BLACK_SECOND_SKILL_H_

#include "Object/Skill/Skill.h"


class WhiteBlackSecond : public Skill
{
private:
	enum
	{
		WHITE_BLACK_SECOND_MAX =  3
	};
	Skill skills[ WHITE_BLACK_SECOND_MAX ];

public:
	WhiteBlackSecond ();

	~WhiteBlackSecond ();

	void Init ( std::string _filename, std::wstring _path );

	void Update ();

	void Draw ();

	void Move ();

	void SetPosition ( const D3DXVECTOR2& _pos, unsigned int dirFlg );

	AnimationData& GetAnimationData ();

};

#endif