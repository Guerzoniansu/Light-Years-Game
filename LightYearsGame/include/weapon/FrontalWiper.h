#pragma once
#include <SFML/Graphics.hpp>
#include "weapon/bulletshooter.h"

namespace ly
{
	class FrontalWiper : public Shooter
	{
	public:
		FrontalWiper(Actor* owner, 
			float coolDownTime = 0.3f, 
			const sf::Vector2f& localOffset = { 0.f, 0.f },
			float width = 48.f
		);

		virtual void incrementLevel(int amt = 1) override;
		virtual void setCurrentLevel(int level) override;

	private:
		virtual void shootImpl() override;
		float mWidth;
		BulletShooter mShooter1;
		BulletShooter mShooter2;
		BulletShooter mShooter3;
		BulletShooter mShooter4;

		BulletShooter mShooter5;
		BulletShooter mShooter6;
	};
}