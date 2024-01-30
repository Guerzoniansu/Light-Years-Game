#pragma once
#include "gameplay/gamestage.h"
#include <SFML/Graphics.hpp>
#include "framework/timer.h"

namespace ly
{
	class VanguardStage : public GameStage
	{
	public:
		VanguardStage(World* world);
		virtual void startStage() override;

	private:
		float mSpawnInterval;
		float mSwitchInterval;
		float mSpawnDistanceToEdge;

		sf::Vector2f mLeftSpawnLoc;
		sf::Vector2f mRightSpawnLoc;

		sf::Vector2f mSpawnLoc;

		TimerHandle mSpawnTimerHandle;
		TimerHandle mSwitchTimerHandle;

		int mRowsToSpawn;
		int mRowSpawnCount;

		int mVanguardsPerRow;
		int mCurrentRowVanguardCount;

		virtual void stageFinished() override;

		void spawnVanguard();
		void switchRow();
	};
}




