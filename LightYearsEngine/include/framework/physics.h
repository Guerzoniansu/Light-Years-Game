#pragma once
#include <box2d/b2_world.h> 
#include "framework/core.h"
#include "actor.h"

namespace ly
{
	class Actor;
	class PhysicsContactListener :public b2ContactListener
	{
		virtual void BeginContact(b2Contact* contact) override;
		virtual void EndContact(b2Contact* contact) override;
	};
	class Physics
	{
	public:
		static Physics& get();
		void step(float deltaTime);

		b2Body* addListener(Actor* listener);
		void removeListener(b2Body* bodyToRemove);

		float getPhysicsScale() { return mPhysicsScale; }
		static void cleanUp();
	protected:
		Physics();
	private:
		void processPendingRemoveListeners();
		static unique<Physics> mPhysics;
		b2World mPhysicsWorld;
		float mPhysicsScale;
		int mVelocityIterations;
		int mPositionIterations;
		PhysicsContactListener mContactListener;

		set<b2Body*> mPendingRemoveListeners;
	};
}