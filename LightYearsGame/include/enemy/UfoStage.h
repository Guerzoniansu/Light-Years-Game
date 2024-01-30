#pragma once
#include "gameplay/gamestage.h"
#include "framework/world.h"
#include <SFML/Graphics.hpp>
#include "framework/timer.h"

namespace ly
{
	class UfoStage : public GameStage
	{
	public:
		UfoStage(World* world);
		virtual void startStage() override;

	private:
		float mSpawnInterval;

		sf::Vector2f mSpawnLoc;

		int mSpawnAmt;
		int mCurrentSpawnAmt;

		float mUfoSpeed;

		TimerHandle mSpawnTimer;

		sf::Vector2f getRandomSpawnLocation() const;

		virtual void stageFinished() override;
		void spawnUfo();
	};
}