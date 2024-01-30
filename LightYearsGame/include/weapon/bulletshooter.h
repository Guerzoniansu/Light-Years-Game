#pragma once
#include <SFML/System.hpp>
#include "weapon/shooter.h"

namespace ly
{
	class BulletShooter:public Shooter
	{
	public:
		BulletShooter(Actor* owner,
			float coolDownTime = 1.0f,
			sf::Vector2f localPositionOffset = { 0.f, 0.f }, 
			float localRotationOffset = 0.f,
			const std::string bulletTexturePath = "SpaceShooterRedux/PNG/Lasers/laserBlue01.png"
		);
		virtual bool isOnCoolDown() const override;
		virtual void incrementLevel(int amt = 1) override;

		void setBulletTexturePath(const std::string& newBulletTexturePath);

	private:
		virtual void shootImpl() override;
		sf::Clock mCoolDownClock;
		float mCoolDownTime;
		sf::Vector2f mLocalPositionOffset;
		float mLocalRotationOffset;
		std::string mBulletTexturePath;
	};
}