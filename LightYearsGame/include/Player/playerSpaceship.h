#pragma once
#include "SpaceShip/spaceship.h"
#include "framework/math.h"
#include "weapon/shooter.h"
#include "weapon/bulletshooter.h"
#include "framework/timer.h"

namespace ly
{
	class Shooter;
	class PlayerSpaceShip :public SpaceShip
	{
	public:
		PlayerSpaceShip(World* owningWorld, const std::string path = "SpaceShooterRedux/PNG/playerShip1_blue.png");
		virtual void Tick(float deltaTime) override;
		virtual void shoot() override;

		void setShooter(unique<Shooter>& newShooter);
		virtual void applyDamage(float amt) override;

		virtual void BeginPlay() override;
	private:
		void handleInput();
		void normalizeInput();
		void clampInputOnEdge();
		void consumeInput(float deltaTime);
		void setSpeed(float newSpeed);
		void stopInvulnerableTime();
		void updateInvulnerable(float deltaTime);
		float getSpeed();
		sf::Vector2f mMoveInput;
		float mSpeed;

		unique<Shooter> mShooter;

		float mInvulnerableTime;
		TimerHandle mInvulnerableTimerHandle;

		bool mInvulnerable;

		float mInvulnerableFlashInterval;
		float mInvulnerableFlashTimer;
		float mInvulnerableFlashDirection;
	};
}