#ifndef _SKILL_H_
#define _SKILL_H_

//#include <Box2D\Dynamics\b2Body.h>
#include "Object/Skill/SkillDefine.h"
#include "CharacterController/CharacterInfo.h"
#include "Object/ObjectParameter.h"
#include <memory>
#include <vector>
#include <string>
//#include "World/World.h"

class Sprite;
struct D3DXVECTOR2;
struct CellData;
struct CollisionShape;
class b2Body;

class Skill
{
protected:
	std::shared_ptr< Sprite > skillAnim;
	AnimationData animSkill;
	int frameCount = 0;
	int animeMax = 0;
	int nowAnime = 0;
	bool skillFlg = false;
	D3DXVECTOR2 pos;
	std::vector<std::shared_ptr<CellData>>::iterator currentCell;

	unsigned int dirFlg;
	//b2Body* body;

public:
	Skill (){}

	~Skill (){}

	void Init ( std::string _filename, std::wstring _path, int skill_id );

	virtual void Update ();

	virtual void Draw ();

	virtual void SetPosition ( const D3DXVECTOR2& _pos, unsigned int _dirFlg );

	D3DXVECTOR2& GetPosition ();

	virtual void Move (){}

	void SkillOn ();

	void SkillOff ();

	//b2Body& Getb2Body ();

	bool IsActive ();

	void SetAttachFixture ( b2Body* _body );

private:
	//void AttachFixture ( std::vector<std::shared_ptr<struct CollisionShape>>& shapes );


};

#endif