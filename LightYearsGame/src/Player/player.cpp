#include "Player/player.h"
#include "Player/playerSpaceship.h"

namespace ly
{
	Player::Player()
		:mLifeCount{3},
		mScore{0},
		mCurrentPlayerSpaceShip{}
	{
	}
	weak<PlayerSpaceShip> Player::spawnSpaceShip(World* world)
	{
		if (mLifeCount > 0)
		{
			--mLifeCount;
			auto windowSize = world->getWindowSize();
			mCurrentPlayerSpaceShip = world->spawnActor<PlayerSpaceShip>();
			mCurrentPlayerSpaceShip.lock()->setActorLocation(sf::Vector2f(windowSize.x / 2.f, windowSize.y - 100.f));
			mCurrentPlayerSpaceShip.lock()->setActorRotation(0.f);
			onLifeChange.broadCast(mLifeCount);

			return mCurrentPlayerSpaceShip;
		}
		else
		{
			mCurrentPlayerSpaceShip = weak<PlayerSpaceShip>{};
			onLifeExhausted.broadCast();
		}

		return weak<PlayerSpaceShip>{};
	}
	void Player::addLifeCount(unsigned int count)
	{
		if (count > 0)
		{
			mLifeCount += count;
			onLifeChange.broadCast(mLifeCount);
		}
	}
	
	void Player::addScore(unsigned int amt)
	{
		if (amt > 0)
		{
			mScore += amt;
			onScoreChange.broadCast(mScore);
		}
	}
}