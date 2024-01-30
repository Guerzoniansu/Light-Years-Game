#include "weapon/threeWayShooter.h"

namespace ly
{
	ThreeWayShooter::ThreeWayShooter(Actor* owner, float coolDownTime, const sf::Vector2f& localOffset)
		:Shooter{owner},
		mShooterLeft{ owner, coolDownTime, localOffset + sf::Vector2f{0.f, 15.f}, -30.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"},
		mShooterMid{ owner, coolDownTime, localOffset, 0.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png" },
		mShooterRight{ owner, coolDownTime, localOffset + sf::Vector2f{0.f, -15.f}, 30.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png" },
		mTopLevelShooterLeft{ owner, coolDownTime, localOffset + sf::Vector2f{0.f, 10.f}, -15.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png" },
		mTopLevelShooterRight{ owner, coolDownTime, localOffset + sf::Vector2f{0.f, -10.f}, 15.f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png" }
	{
		
	}

	void ThreeWayShooter::incrementLevel(int amt)
	{
		Shooter::incrementLevel();
		mShooterLeft.incrementLevel(amt);
		mShooterMid.incrementLevel(amt);
		mShooterRight.incrementLevel(amt);
		mTopLevelShooterLeft.incrementLevel(amt);
		mTopLevelShooterRight.incrementLevel(amt);
	}

	void ThreeWayShooter::setCurrentLevel(int level)
	{
		Shooter::setCurrentLevel(level);
		mShooterLeft.setCurrentLevel(level);
		mShooterMid.setCurrentLevel(level);
		mShooterRight.setCurrentLevel(level);

		mTopLevelShooterLeft.setCurrentLevel(level);
		mTopLevelShooterRight.setCurrentLevel(level);
	}

	void ThreeWayShooter::shootImpl()
	{
		mShooterLeft.shoot();
		mShooterMid.shoot();
		mShooterRight.shoot();

		if (getCurrentLevel() == getMaxLevel())
		{
			mTopLevelShooterLeft.shoot();
			mTopLevelShooterRight.shoot();
		}
	}
}