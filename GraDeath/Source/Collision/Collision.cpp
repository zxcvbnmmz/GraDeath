#include "Collision/Collision.h"
#include "World/World.h"
#include <Box2D\Box2D.h>
#include "Object/Player.h"

bool Collision::Collide(Player* playerA, Player* playerB){
	b2Body* bodyA = playerA->GetBody();
	b2Body* bodyB = playerB->GetBody();

	const b2Transform& xfA = bodyA->GetTransform();
	const b2Transform& xfB = bodyB->GetTransform();
	b2Fixture* fixtureA = bodyA->GetFixtureList();
	while (fixtureA != NULL){
		const b2Shape* shapeA = fixtureA->GetShape();
		b2Fixture* fixtureB = bodyB->GetFixtureList();

		while (fixtureB != NULL){
			const b2Shape* shapeB = fixtureB->GetShape();

			// �t�B���^�[�̃}�X�N�l�ƃJ�e�S���l���r�b�g���Z�łǂ���������
			// ���̕ӂ��box2d�̏Փ˔���Ɠ���
			const b2Filter& filterA = fixtureA->GetFilterData();
			const b2Filter& filterB = fixtureB->GetFilterData();
			bool collide = (filterA.maskBits & filterB.categoryBits) != 0 && (filterA.categoryBits & filterB.maskBits) != 0;

			if (collide){
				// b2TestOverlap�̓V�F�C�v�ƃV�F�C�v���Փ˂��Ă��邩���肷��֐�
				bool touching = b2TestOverlap(shapeA, 0, shapeB, 0, xfA, xfB);
				if (touching){


					return true;
				}
			}
			fixtureB = fixtureB->GetNext();
		}
		fixtureA = fixtureA->GetNext();
	}
	return false;
}

bool Collision::CollideToStage(Player* body, b2Body* breakableStage){
	return false;
}

bool Collision::CollideOtherFloors(Player* player, b2Body* unbreakableStage){	
	b2Body* playerBody = player->GetBody();

	const b2Transform& xfA = playerBody->GetTransform();
	const b2Transform& stageTrans = unbreakableStage->GetTransform();

	b2Fixture* fixtureA = playerBody->GetFixtureList();
	while (fixtureA != NULL){
		const b2Shape* shapeA = fixtureA->GetShape();
		b2Fixture* fixtureB = unbreakableStage->GetFixtureList();

		while (fixtureB != NULL){
			const b2Shape* shapeB = fixtureB->GetShape();

			// b2TestOverlap�̓V�F�C�v�ƃV�F�C�v���Փ˂��Ă��邩���肷��֐�
			bool touching = b2TestOverlap(shapeA, 0, shapeB, 0, xfA, stageTrans);
			if (touching){
				b2ContactListener l;
				b2ContactManager m;
				m.m_contactListener = &l;

				b2Manifold manifold;
				

				return true;
				
			}
			fixtureB = fixtureB->GetNext();
		}
		fixtureA = fixtureA->GetNext();
	}
	return false;
}
