#include "Collision/Collision.h"
#include "World/World.h"
#include <Box2D\Box2D.h>
#include "Object/ObjectMask.h"
#include "Object/Player.h"
#include "object/CollisionShape.h"
#include "Manager/HitpointManager.h"

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
					CollisionShape* collisionShape;
					Player* damagedPlayer;
					float strength;

					if (filterA.categoryBits & MASK_COL_ATK){
						collisionShape = (CollisionShape*)fixtureA->GetUserData();
						damagedPlayer = playerB;
					}
					else{
						collisionShape = (CollisionShape*)fixtureB->GetUserData();
						damagedPlayer = playerA;
					}

					strength = collisionShape->GetStrength();
					HitPointManager::HitDamage(damagedPlayer, strength);

					return true;
				}
			}
			fixtureB = fixtureB->GetNext();
		}
		fixtureA = fixtureA->GetNext();
	}
	return false;
}

