#include "Collision/Collision.h"
#include "World/World.h"
#include <Box2D\Box2D.h>
#include "Object/ObjectMask.h"
#include "Object/Player.h"
#include "Object/CollisionShape.h"
#include "Manager/HitpointManager.h"
#include "CharacterController/PlayerController/PlayerController.h"
#include "CharacterController/CharacterController.h"

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

			// フィルターのマスク値とカテゴリ値をビット演算でどうこうする
			// この辺りはbox2dの衝突判定と同じ
			const b2Filter& filterA = fixtureA->GetFilterData();
			const b2Filter& filterB = fixtureB->GetFilterData();
			bool collide = (filterA.maskBits & filterB.categoryBits) != 0 && (filterA.categoryBits & filterB.maskBits) != 0;

			if (collide){
				// b2TestOverlapはシェイプとシェイプが衝突しているか判定する関数
				bool touching = b2TestOverlap(shapeA, 0, shapeB, 0, xfA, xfB);
				if (touching){
					Player* damagedPlayer;
					CollisionShape* shape;
					float strength = 0;

					if (filterA.categoryBits & MASK_COL_ATK){
						shape = (CollisionShape*)fixtureA->GetUserData();
						damagedPlayer = playerB;
					}
					else if (filterB.categoryBits & MASK_COL_ATK){
						shape = (CollisionShape*)fixtureB->GetUserData();
						damagedPlayer = playerA;
					}else{
						break;
					}

					strength = shape->GetStrength();
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

bool Collision::CollideToStage(Player* body, b2Body* stage, CharacterController* controller){
	CollideFloor(body, stage, controller);

	return false;
}

bool Collision::CollideFloor(Player* player, b2Body* unbreakableStage, CharacterController* controller){
	assert(controller != nullptr);

	if (controller->GetCurrentAction() != ACTION_JUMP_FALL){
		return false;
	}

	b2Body* playerBody = player->GetBody();

	const b2Transform& xfA = playerBody->GetTransform();
	const b2Transform& stageTrans = unbreakableStage->GetTransform();

	b2Fixture* fixtureA = playerBody->GetFixtureList();
	while (fixtureA != NULL){
		const b2Shape* shapeA = fixtureA->GetShape();
		b2Fixture* fixtureB = unbreakableStage->GetFixtureList();

		while (fixtureB != NULL){
			const b2Shape* shapeB = fixtureB->GetShape();

			// b2TestOverlapはシェイプとシェイプが衝突しているか判定する関数
			bool touching = b2TestOverlap(shapeA, 0, shapeB, 0, xfA, stageTrans);
			if (touching){
				b2Manifold manifold;

				if (shapeA->m_type == b2Shape::e_circle){
					const b2CircleShape* polygonShapeA = reinterpret_cast<const b2CircleShape*>(shapeA);
					if (shapeB->m_type == b2Shape::e_circle){
						const b2CircleShape* polygonShapeB = reinterpret_cast<const b2CircleShape*>(shapeB);
						b2CollideCircles(&manifold, polygonShapeA, xfA, polygonShapeB, stageTrans);
					}
					else if (shapeB->m_type == b2Shape::e_polygon){
						const b2PolygonShape* polygonShapeB = reinterpret_cast<const b2PolygonShape*>(shapeB);
						b2CollidePolygonAndCircle(&manifold, polygonShapeB, stageTrans, polygonShapeA, xfA);
					}
				}
				else if (shapeA->m_type == b2Shape::e_polygon){
					const b2PolygonShape* polygonShapeA = reinterpret_cast<const b2PolygonShape*>(shapeA);
					if (shapeB->m_type == b2Shape::e_circle){
						const b2CircleShape* polygonShapeB = reinterpret_cast<const b2CircleShape*>(shapeB);
						b2CollidePolygonAndCircle(&manifold, polygonShapeA, xfA, polygonShapeB, stageTrans);
					}
					else if (shapeB->m_type == b2Shape::e_polygon){
						const b2PolygonShape* polygonShapeB = reinterpret_cast<const b2PolygonShape*>(shapeB);
						b2CollidePolygons(&manifold, polygonShapeA, xfA, polygonShapeB, stageTrans);
					}
				}

				if (abs(manifold.localNormal.y) > 0.5 && player->GetBody()->GetLinearVelocity().y > 10){
					controller->ChangeAction(ACTION_JUMP_LAND, false);
				}

				return true;
				
			}
			fixtureB = fixtureB->GetNext();
		}
		fixtureA = fixtureA->GetNext();
	}
	return false;
}

bool Collision::CollideSkill(Player* player, b2Body* skill){
	if (skill == nullptr){
		return false;
	}

	b2Body* bodyA = player->GetBody();
	b2Body* bodyB = skill;

	const b2Transform& xfA = bodyA->GetTransform();
	const b2Transform& xfB = bodyB->GetTransform();
	b2Fixture* fixtureA = bodyA->GetFixtureList();
	while (fixtureA != NULL){
		const b2Shape* shapeA = fixtureA->GetShape();
		b2Fixture* fixtureB = bodyB->GetFixtureList();

		while (fixtureB != NULL){
			const b2Shape* shapeB = fixtureB->GetShape();

			// フィルターのマスク値とカテゴリ値をビット演算でどうこうする
			// この辺りはbox2dの衝突判定と同じ
			const b2Filter& filterA = fixtureA->GetFilterData();
			const b2Filter& filterB = fixtureB->GetFilterData();
			bool collide = (filterA.maskBits & filterB.categoryBits) != 0 && (filterA.categoryBits & filterB.maskBits) != 0;

			if (collide){
				// b2TestOverlapはシェイプとシェイプが衝突しているか判定する関数
				bool touching = b2TestOverlap(shapeA, 0, shapeB, 0, xfA, xfB);
				if (touching){
					CollisionShape* shape;
					float strength = 0;

					shape = (CollisionShape*)fixtureB->GetUserData();

					strength = shape->GetStrength();
					HitPointManager::HitDamage(player, strength);

					return true;
				}
			}
			fixtureB = fixtureB->GetNext();
		}
		fixtureA = fixtureA->GetNext();
	}
	return false;
}
