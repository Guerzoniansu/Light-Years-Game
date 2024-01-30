#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>
#include <box2d/b2_world_callbacks.h>
#include <box2d/b2_contact.h>

#include "framework/physics.h"
#include "framework/actor.h"
#include "framework/math.h"

namespace ly
{
	unique<Physics> Physics::mPhysics{ nullptr };
	void Physics::cleanUp()
	{
		mPhysics = std::move(unique<Physics>{new Physics});//The previous physic system will be destroyed because unique ptr
	}
	Physics::Physics()
		:mPhysicsWorld{b2Vec2{0, 0}},
		mPhysicsScale{0.01f},
		mVelocityIterations{8},
		mPositionIterations{3},
		mContactListener{},
		mPendingRemoveListeners{}
	{
		mPhysicsWorld.SetContactListener(&mContactListener);
		mPhysicsWorld.SetAllowSleeping(false);
	}
	void Physics::processPendingRemoveListeners()
	{
		for (auto listener: mPendingRemoveListeners)
		{
			mPhysicsWorld.DestroyBody(listener);
		}

		mPendingRemoveListeners.clear();
	}
	Physics& Physics::get()
	{
		if (!mPhysics)
		{
			mPhysics = std::move(unique<Physics>{new Physics});
		}
		return *mPhysics;
	}
	void Physics::step(float deltaTime)
	{
		processPendingRemoveListeners();
		mPhysicsWorld.Step(deltaTime, mVelocityIterations, mPositionIterations);
	}
	b2Body* Physics::addListener(Actor* listener)
	{
		if (listener->IsPendingDestroy())
		{
			return nullptr;
		}
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;

		bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(listener);
		bodyDef.position.Set(listener->getActorLocation().x * getPhysicsScale(), listener->getActorLocation().y * getPhysicsScale());
		bodyDef.angle = degreesToRadians(listener->getActorRotation());

		b2Body* body = mPhysicsWorld.CreateBody(&bodyDef);

		b2PolygonShape shape;
		auto bounds = listener->getActorGlobalBounds();
		shape.SetAsBox((bounds.width / 2.f) * getPhysicsScale(), (bounds.height / 2.f) * getPhysicsScale());

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &shape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
		fixtureDef.isSensor = true;

		body->CreateFixture(&fixtureDef);

		return body;
	}
	void Physics::removeListener(b2Body* bodyToRemove)
	{
		mPendingRemoveListeners.insert(bodyToRemove);
	}
	void PhysicsContactListener::BeginContact(b2Contact* contact)
	{
		Actor* actorA = reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
		Actor* actorB = reinterpret_cast<Actor*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

		if (actorA && !actorA->IsPendingDestroy())
		{
			actorA->onActorBeginOverlap(actorB);
		}
		if (actorB && !actorB->IsPendingDestroy())
		{
			actorB->onActorBeginOverlap(actorA);
		}
	}
	void PhysicsContactListener::EndContact(b2Contact* contact)
	{
		Actor* actorA = nullptr;
		Actor* actorB = nullptr;

		if (contact->GetFixtureA() && contact->GetFixtureA()->GetBody())
		{
			actorA = reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
		}
		if (contact->GetFixtureB() && contact->GetFixtureB()->GetBody())
		{
			actorB = reinterpret_cast<Actor*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);
		}
		if (actorA && !actorA->IsPendingDestroy())
		{
			actorA->onActorEndOverlap(actorB);
		}
		if (actorB && !actorB->IsPendingDestroy())
		{
			actorB->onActorEndOverlap(actorA);
		}
	}
}