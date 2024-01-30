#pragma once
#include "gameplay/gamestage.h"
#include "framework/timer.h"
#include <SFML/Graphics.hpp>

namespace ly
{
	class ChaosStage : public GameStage
	{
	public:
		ChaosStage(World* world);

		virtual void startStage() override;

	private:
		virtual void stageFinished() override;
		void spawnVanguard();
		void spawnTwinBlade();
		void spawnHexagon();
		void spawnUFO();

		void increaseDifficulty();

		void stageDurationReached();

		sf::Vector2f getRandomSpawnLocationTop() const;
		sf::Vector2f getRandomSpawnLocationSide() const;

		float mSpawnInterval;
		float mMinSpawnInterval;

		float mSpawnIntervalDecrement;
		float mSpawnIntervalDecrementInterval;

		float mStageDuration;

		TimerHandle mDifficultTimerHandle;
		TimerHandle mSpawnTimer;

	};
}