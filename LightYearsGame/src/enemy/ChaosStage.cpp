#include "enemy/ChaosStage.h"
#include "gameplay/gamestage.h"
#include "enemy/vanguard.h"
#include "enemy/TwinBlade.h"
#include "enemy/hexagon.h"
#include "enemy/ufo.h"
#include "framework/world.h"
#include "framework/math.h"

#include <iostream>

namespace ly
{
	ChaosStage::ChaosStage(World* world)
		:GameStage{world},
		mSpawnInterval{4.f},
		mMinSpawnInterval{0.8f},
		mSpawnIntervalDecrement{0.5f},
		mSpawnIntervalDecrementInterval{5.f},
		mStageDuration{90.f}
	{

	}
	void ChaosStage::startStage()
	{
		mSpawnTimer = TimerManager::get().setTimer(getWeakRef(), &ChaosStage::spawnVanguard, mSpawnInterval);
		mDifficultTimerHandle = TimerManager::get().setTimer(getWeakRef(), 
			&ChaosStage::increaseDifficulty, mSpawnIntervalDecrementInterval, true);
		TimerManager::get().setTimer(getWeakRef(), &ChaosStage::stageDurationReached, mStageDuration);
	}
	void ChaosStage::stageFinished()
	{
		TimerManager::get().clearTimer(mDifficultTimerHandle);
		TimerManager::get().clearTimer(mSpawnTimer);
	}
	void ChaosStage::spawnVanguard()
	{
		weak<Vanguard> newVanguard = getWorld()->spawnActor<Vanguard>();
		newVanguard.lock()->setActorLocation(getRandomSpawnLocationTop());
		mSpawnTimer = TimerManager::get().setTimer(getWeakRef(), &ChaosStage::spawnTwinBlade, mSpawnInterval);
	}
	void ChaosStage::spawnTwinBlade()
	{
		weak<TwinBlade> newTwinBlade = getWorld()->spawnActor<TwinBlade>();
		newTwinBlade.lock()->setActorLocation(getRandomSpawnLocationTop());
		mSpawnTimer = TimerManager::get().setTimer(getWeakRef(), &ChaosStage::spawnHexagon, mSpawnInterval);
	}
	void ChaosStage::spawnHexagon()
	{
		weak<Hexagon> newHexagon = getWorld()->spawnActor<Hexagon>();
		newHexagon.lock()->setActorLocation(getRandomSpawnLocationTop());
		mSpawnTimer = TimerManager::get().setTimer(getWeakRef(), &ChaosStage::spawnUFO, mSpawnInterval);
	}
	void ChaosStage::spawnUFO()
	{
		sf::Vector2f spawnLoc = getRandomSpawnLocationSide();

		auto windowSize = getWorld()->getWindowSize();
		sf::Vector2f center = sf::Vector2f{ windowSize.x / 2.f, windowSize.y / 2.f };
		sf::Vector2f dirToCenter = center - spawnLoc;
		normalize(dirToCenter);

		weak<UFO> newUFO = getWorld()->spawnActor<UFO>(dirToCenter * 200.f);

		newUFO.lock()->setActorLocation(spawnLoc);
		mSpawnTimer = TimerManager::get().setTimer(getWeakRef(), &ChaosStage::spawnVanguard, mSpawnInterval);
	}
	void ChaosStage::increaseDifficulty()
	{
		mSpawnInterval -= mSpawnIntervalDecrement;
		if (mSpawnInterval < mMinSpawnInterval)
		{
			mSpawnInterval = mMinSpawnInterval;
		}
	}
	void ChaosStage::stageDurationReached()
	{
		finishStage();
	}
	sf::Vector2f ChaosStage::getRandomSpawnLocationTop() const
	{
		auto windowSize = getWorld()->getWindowSize();
		float spawnX = randomRange(100.f, windowSize.x - 100.f);
		float spawnY = -50.f;

		return { spawnX, spawnY };
	}
	sf::Vector2f ChaosStage::getRandomSpawnLocationSide() const
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
}