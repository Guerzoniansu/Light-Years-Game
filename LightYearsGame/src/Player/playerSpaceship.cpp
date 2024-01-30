#include "Player/playerSpaceship.h"
#include <SFML/System.hpp>
#include "weapon/bulletshooter.h"
#include "weapon/threeWayShooter.h"
#include "weapon/FrontalWiper.h"

namespace ly
{
	PlayerSpaceShip::PlayerSpaceShip(World* owningWorld, const std::string path)
		:SpaceShip{owningWorld, path},
		mMoveInput{},
		mSpeed{200.f},
		mShooter{ new BulletShooter{this, 0.1f, {50.f, 0.f}} },
		mInvulnerableTime{3.f},
		mInvulnerable{true},
		mInvulnerableFlashInterval{0.5f},
		mInvulnerableFlashTimer{0.f},
		mInvulnerableFlashDirection{1.f}
	{
		setTeamID(1);
	}
	void PlayerSpaceShip::Tick(float deltaTime)
	{
		SpaceShip::Tick(deltaTime);
		handleInput();
		consumeInput(deltaTime);
		updateInvulnerable(deltaTime);
	}
	void PlayerSpaceShip::shoot()
	{
		if (mShooter)
		{
			mShooter->shoot();
		}
	}
	void PlayerSpaceShip::setShooter(unique<Shooter>& newShooter)
	{
		if (mShooter && typeid(*mShooter.get()) == typeid(*newShooter.get()))
		{
			mShooter->incrementLevel();
			return;
		}

		mShooter = std::move(newShooter);
	}
	void PlayerSpaceShip::handleInput()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
		{
			mMoveInput.y = -1.f;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			mMoveInput.y = 1.f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		{
			mMoveInput.x = -1.f;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			mMoveInput.x = 1.f;
		}
		clampInputOnEdge();
		normalizeInput();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			shoot();
		}
	}

	void PlayerSpaceShip::normalizeInput()
	{
		normalize<float>(mMoveInput);
	}

	void PlayerSpaceShip::clampInputOnEdge()
	{
		sf::Vector2f actorLocation = getActorLocation();
		if (actorLocation.x < 0 && mMoveInput.x == -1.f)
		{
			mMoveInput.x = 0.f;
		}
		if (actorLocation.x > getWindowSize().x && mMoveInput.x == 1.f)
		{
			mMoveInput.x = 0.f;
		}
		if (actorLocation.y < 0 && mMoveInput.y == -1.f)
		{
			mMoveInput.y = 0.f;
		}
		if (actorLocation.y > getWindowSize().y && mMoveInput.y == 1.f)
		{
			mMoveInput.y = 0.f;
		}
	}

	void PlayerSpaceShip::consumeInput(float deltaTime)
	{
		setVelocity(mMoveInput * mSpeed);
		mMoveInput.x = mMoveInput.y = 0.f;
	}

	void PlayerSpaceShip::setSpeed(float newSpeed)
	{
		mSpeed = newSpeed;
	}
	float PlayerSpaceShip::getSpeed()
	{
		return mSpeed;
	}

	void PlayerSpaceShip::applyDamage(float amt)
	{
		if (!mInvulnerable)
		{
			SpaceShip::applyDamage(amt);
		}

	}

	void PlayerSpaceShip::BeginPlay()
	{
		SpaceShip::BeginPlay();
		TimerManager::get().setTimer(getWeakRef(), &PlayerSpaceShip::stopInvulnerableTime, mInvulnerableTime);
	}

	void PlayerSpaceShip::stopInvulnerableTime()
	{
		getSprite().setColor({ 255, 255, 255, 255 });
		mInvulnerable = false;
	}

	void PlayerSpaceShip::updateInvulnerable(float deltaTime)
	{
		if (!mInvulnerable)
		{
			return;
		}

		mInvulnerableFlashTimer += deltaTime * mInvulnerableFlashDirection;

		if (mInvulnerableFlashTimer < 0 || mInvulnerableFlashTimer > mInvulnerableFlashInterval)
		{
			mInvulnerableFlashDirection *= -1;
		}

		getSprite().setColor(lerpColor({ 255, 255, 255, 64 }, { 255, 255, 255, 255 },
			mInvulnerableFlashTimer / mInvulnerableFlashInterval));
	}
}
