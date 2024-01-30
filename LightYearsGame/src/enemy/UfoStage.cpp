#include "enemy/UfoStage.h"
#include "framework/timer.h"
#include "enemy/ufo.h"
#include "framework/math.h"
#include "weapon/bulletshooter.h"

namespace ly
{
	UfoStage::UfoStage(World* world)
		:GameStage{world},
		mSpawnInterval{4.0f},
		mSpawnAmt{10},
		mCurrentSpawnAmt{0},
		mUfoSpeed{200.f}
	{

	}

	void UfoStage::startStage()
	{
		mSpawnTimer = TimerManager::get().setTimer(getWeakRef(), &UfoStage::spawnUfo, mSpawnInterval, true);
	}

	sf::Vector2f UfoStage::getRandomSpawnLocation() const
	{
		auto windowSize = getWorld()->getWindowSize();
		float spawnLeft = randomRange(-1.f, 1.f);
		float spawnLocX = 0.f;

		if (spawnLeft < 0.f)
		{
			spawnLocX = windowSize.x + 100.f;
		}
		else
		{
			spawnLocX = -100.f;
		}

		float spawnLocY = randomRange(0, windowSize.y);
		return sf::Vector2f{ spawnLocX, spawnLocY };
	}

	void UfoStage::stageFinished()
	{
		TimerManager::get().clearTimer(mSpawnTimer);
	}

	void UfoStage::spawnUfo()
	{
		sf::Vector2f spawnLoc = getRandomSpawnLocation();

		auto windowSize = getWorld()->getWindowSize();
		sf::Vector2f center{ windowSize.x / 2.f, windowSize.y / 2.f };

		sf::Vector2f spawnLocationToCenter{ center.x - spawnLoc.x, center.y - spawnLoc.y };
		normalize(spawnLocationToCenter);

		sf::Vector2f spawnVelocity = spawnLocationToCenter * mUfoSpeed;

		weak<UFO> newUFO = getWorld()->spawnActor<UFO>(spawnVelocity);
		newUFO.lock()->setActorLocation(spawnLoc);

		if ( ++mCurrentSpawnAmt == mSpawnAmt)
		{
			finishStage();
		}
	}
}