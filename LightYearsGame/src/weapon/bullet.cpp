#include "weapon/bullet.h"
#include "framework/world.h"
#include <iostream>

namespace ly
{
	Bullet::Bullet(World* world, Actor* owner, const std::string& texturePath, float speed, float damage)
		:Actor{ world, texturePath },
		mOwner{ owner },
		mSpeed{speed},
		mDamage{damage}
	{
		setTeamID(owner->getTeamID());
	}
	float Bullet::getSpeed() const
	{ 
		return mSpeed;
	}
	void Bullet::setSpeed(float newSpeed) 
	{ 
		mSpeed = newSpeed;
	}
	void Bullet::setDamage(float newDamage) 
	{ 
		mDamage = newDamage;
	}
	void Bullet::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		move(deltaTime);
		if (isActorOutOfWindowBounds())
		{
			Destroy();
		}
	}
	void Bullet::BeginPlay()
	{
		Actor::BeginPlay();
		setEnablePhysics(true);
	}
	void Bullet::onActorBeginOverlap(Actor* other)
	{
		if (isOtherHostile(other))
		{
			other->applyDamage(getDamage());
			Destroy();
		}
	}
	void Bullet::move(float deltaTime)
	{
		addActorLocationOffset(getActorForwardDirection() * mSpeed * deltaTime);//When a bullet is shoot out, it will go forward indefinitely
	}
}