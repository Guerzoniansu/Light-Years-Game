#pragma once
#include "framework/world.h"
#include "Player/playerSpaceship.h"
#include "framework/core.h"
#include "framework/timer.h"
#include "Player/PlayerManager.h"
#include "widgets/GamePlayHUD.h"

namespace ly
{
	class PlayerSpaceShip;
	class GamePlayHUD;
	class GameLevelOne : public World
	{
	public:
		GameLevelOne(Application* owningApp);

	private:
		virtual void AllGameStageFinished() override;
		virtual void GameLevelOne::BeginPlay() override;
		weak<PlayerSpaceShip> mPlayerSpaceShip;
		weak<GamePlayHUD> mGamePlayHUD;
		void playerSpaceShipDestroyed(Actor* destroyedPlayerSpaceShip);
		TimerHandle timerHandle_Test;
		virtual void initGameStages() override;

		void QuitGame();
		void RestartGame();

		void GameOver();

		void spawnCosmetics();
	};
}