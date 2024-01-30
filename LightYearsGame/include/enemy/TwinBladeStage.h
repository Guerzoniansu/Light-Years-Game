#pragma once
#include <SFML/Graphics.hpp>
#include "framework/timer.h"
#include "gameplay/gamestage.h"

namespace ly
{
	class TwinBladeStage : public GameStage
	{
	public:
		TwinBladeStage(World* world);
		virtual void startStage() override;

	private:
		void spawnTwinBlade();
		virtual void stageFinished() override;
		float mSpawnInterval;
		float mSpawnDistanceToCenter;

		sf::Vector2f mLeftSpawnLoc;
		sf::Vector2f mRightSpawnLoc;
		sf::Vector2f mSpawnLoc;

		int mSpawnAmt;
		int mCurrentSpawnCount;

		TimerHandle mSpawnTimerHandle;
	};
}