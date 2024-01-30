#pragma once
#include <SFML/Graphics.hpp>
#include "framework/timer.h"
#include "gameplay/gamestage.h"

namespace ly
{
	class HexagonStage : public GameStage
	{
	public:
		HexagonStage(World* world);
		virtual void startStage() override;
	private:
		virtual void stageFinished() override;
		void spawnHexagon();

		float mSpawnInterval;
		float mSideSpawnOffset;
		int mSpawnGroupAmt;
		int mCurrentSpawnCount;

		sf::Vector2f mMidSpawnLoc;
		sf::Vector2f mLeftSpawnLoc;
		sf::Vector2f mRightSpawnLoc;

		TimerHandle mSpawnTimerHandle;
	};
}