#include "weapon/FrontalWiper.h"

namespace ly
{
	FrontalWiper::FrontalWiper(Actor* owner, float coolDownTime, const sf::Vector2f& localOffset, float width)
		:Shooter{ owner },
		mWidth{width},
		mShooter1{ owner, coolDownTime, {localOffset.x, localOffset.y - width / 2.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png" },
		mShooter2{ owner, coolDownTime, {localOffset.x, localOffset.y - width / 6.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserBlue07.png" },
		mShooter3{ owner, coolDownTime, {localOffset.x, localOffset.y + width / 6.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserBlue07.png" },
		mShooter4{ owner, coolDownTime, {localOffset.x, localOffset.y + width / 2.f}, 0.f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png" },
		mShooter5{ owner, coolDownTime, {localOffset.x, localOffset.y - width / 1.5f}, 7.5f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png" },
		mShooter6{ owner, coolDownTime, {localOffset.x, localOffset.y + width / 1.5f}, -7.5f, "SpaceShooterRedux/PNG/Lasers/laserGreen11.png" }
	{

	}

	void FrontalWiper::incrementLevel(int amt)
	{
		Shooter::incrementLevel();
		mShooter1.incrementLevel(amt);
		mShooter2.incrementLevel(amt);
		mShooter3.incrementLevel(amt);
		mShooter4.incrementLevel(amt);
		mShooter5.incrementLevel(amt);
		mShooter6.incrementLevel(amt);
	}

	void FrontalWiper::setCurrentLevel(int level)
	{
		Shooter::setCurrentLevel(level);
		mShooter1.setCurrentLevel(level);
		mShooter2.setCurrentLevel(level);
		mShooter3.setCurrentLevel(level);
		mShooter4.setCurrentLevel(level);
		mShooter5.setCurrentLevel(level);
		mShooter6.setCurrentLevel(level);
	}

	void FrontalWiper::shootImpl()
	{
		mShooter1.shoot();
		mShooter2.shoot();
		mShooter3.shoot();
		mShooter4.shoot();

		if (getCurrentLevel() == getMaxLevel())
		{
			mShooter5.shoot();
			mShooter6.shoot();
		}
	}
}