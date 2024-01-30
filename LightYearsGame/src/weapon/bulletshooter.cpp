#include "weapon/bulletshooter.h"
#include "framework/core.h"
#include "weapon/bullet.h"
#include "framework/world.h"

namespace ly
{
	BulletShooter::BulletShooter(Actor* owner, float coolDownTime, sf::Vector2f localPositionOffset, float localRotationOffset, const std::string bulletTexturePath)
		:Shooter{ owner },
		mCoolDownClock{},
		mCoolDownTime{ coolDownTime },
		mLocalPositionOffset{ localPositionOffset },
		mLocalRotationOffset{ localRotationOffset },
		mBulletTexturePath{bulletTexturePath}
	{
	}
	bool BulletShooter::isOnCoolDown() const
	{
		if (mCoolDownClock.getElapsedTime().asSeconds() > mCoolDownTime / getCurrentLevel())
		{
			return false;
		}
		return true;
	}

	void BulletShooter::incrementLevel(int amt)
	{
		Shooter::incrementLevel(amt);
	}

	void BulletShooter::setBulletTexturePath(const std::string& newBulletTexturePath)
	{
		mBulletTexturePath = newBulletTexturePath;
	}

	void BulletShooter::shootImpl()
	{
		sf::Vector2f ownerForwardDirection = getOwner()->getActorForwardDirection();
		sf::Vector2f ownerRightDirection = getOwner()->getActorRightDirection();
		mCoolDownClock.restart();
		weak<Bullet> newBullet = getOwner()->getWorld()->spawnActor<Bullet>(getOwner(), mBulletTexturePath);
		newBullet.lock()->setActorLocation(getOwner()->getActorLocation() + ownerForwardDirection * mLocalPositionOffset.x + ownerRightDirection * mLocalPositionOffset.y);
		newBullet.lock()->setActorRotation(getOwner()->getActorRotation() + mLocalRotationOffset);
	}
}


