#pragma once
#include "weapon/bulletshooter.h"
#include <SFML/Graphics.hpp>

namespace ly
{
	class ThreeWayShooter : public Shooter
	{
	public:
		ThreeWayShooter(Actor* owner, float coolDownTime = 0.25f, const sf::Vector2f& localOffset = {0.f, 0.f});

		BulletShooter mShooterLeft;
		BulletShooter mShooterMid;
		BulletShooter mShooterRight;

		BulletShooter mTopLevelShooterLeft;
		BulletShooter mTopLevelShooterRight;

		virtual void incrementLevel(int amt = 1) override;
		virtual void setCurrentLevel(int level) override;

	private:
		virtual void shootImpl();
	};
}