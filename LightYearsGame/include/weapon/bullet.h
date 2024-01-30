#pragma once
#include "framework/actor.h"

namespace ly
{
	class Bullet:public Actor
	{
	public:
		Bullet(World* world, Actor* owner, const std::string& texturePath, float speed = 600.f, float damage = 10.f);
		float getSpeed() const;
		void setSpeed(float newSpeed);
		float getDamage() const { return mDamage; };
		void setDamage(float newDamage);

		virtual void Tick(float deltaTime) override;
		virtual void BeginPlay() override;

	private:
		virtual void onActorBeginOverlap(Actor* other) override;
		void move(float deltaTime);
		Actor* mOwner;
		float mSpeed;
		float mDamage;
	};
}