#include "weapon/shooter.h"

namespace ly
{
	void Shooter::shoot()
	{
		if (canShoot() && !isOnCoolDown())
		{
			shootImpl();
		}
	}
	void Shooter::setCurrentLevel(int level)
	{
		mCurrentLevel = level;
	}
	Shooter::Shooter(Actor* owner)
		:mOwner{owner},
		mCurrentLevel{1},
		mMaxLevel{4}
	{

	}

	void Shooter::incrementLevel(int amt)
	{
		if (mCurrentLevel == mMaxLevel)
		{
			return;
		}
		++mCurrentLevel;
	}
}
