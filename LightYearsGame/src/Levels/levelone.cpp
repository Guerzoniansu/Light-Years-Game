#include "Levels/levelone.h"
#include "framework/world.h"
#include "framework/actor.h"
#include "framework/AssetManager.h"
#include "Player/playerSpaceship.h"
#include "enemy/vanguard.h"
#include "framework/timer.h"
#include "gameplay/gamestage.h"
#include "enemy/VanguardStage.h"
#include "enemy/TwinBladeStage.h"
#include "gameplay/waitstage.h"
#include "enemy/HexagonStage.h"
#include "enemy/UfoStage.h"
#include "Player/PlayerManager.h"
#include "enemy/ChaosStage.h"
#include "enemy/BossStage.h"
#include "framework/application.h"
#include "framework/BackDropActor.h"
#include "framework/BackGroundLayer.h"

namespace ly
{
	GameLevelOne::GameLevelOne(Application* owningApp)
		:World{owningApp}
	{
		
	}

	void GameLevelOne::BeginPlay()
	{
		spawnCosmetics();
		Player& newPlayer = PlayerManager::get().createNewPlayer();
		mPlayerSpaceShip = newPlayer.spawnSpaceShip(this);
		mPlayerSpaceShip.lock()->onActorDestroy.bindAction(getWeakRef(), &GameLevelOne::playerSpaceShipDestroyed);
		mGamePlayHUD = spawnHUD<GamePlayHUD>();
		mGamePlayHUD.lock()->onRestartButtonClicked.bindAction(getWeakRef(), &GameLevelOne::RestartGame);
		mGamePlayHUD.lock()->onQuitButtonClicked.bindAction(getWeakRef(), &GameLevelOne::QuitGame);
	}

	void GameLevelOne::playerSpaceShipDestroyed(Actor* destroyedPlayerSpaceShip)
	{
		mPlayerSpaceShip = PlayerManager::get().getPlayer()->spawnSpaceShip(this);
		if (!mPlayerSpaceShip.expired())
		{
			mPlayerSpaceShip.lock()->onActorDestroy.bindAction(getWeakRef(), &GameLevelOne::playerSpaceShipDestroyed);
		}
		else
		{
			GameOver();
		}
	}

	void GameLevelOne::initGameStages()
	{
		addStage(shared<WaitStage>{new WaitStage{ this, 3.f }});
		addStage(shared<VanguardStage>{new VanguardStage{ this }});

		addStage(shared<WaitStage>{new WaitStage{ this, 3.f }});
		addStage(shared<VanguardStage>{new VanguardStage{ this }});

		addStage(shared<WaitStage>{new WaitStage{ this, 3.f }});
		addStage(shared<VanguardStage>{new VanguardStage{ this }});

		addStage(shared<WaitStage>{new WaitStage{ this, 5.f }});
		addStage(shared<TwinBladeStage>{new TwinBladeStage{ this }});

		addStage(shared<WaitStage>{new WaitStage{ this, 3.f }});
		addStage(shared<HexagonStage>{new HexagonStage{ this }});

		addStage(shared<WaitStage>{new WaitStage{ this, 5.f }});
		addStage(shared<TwinBladeStage>{new TwinBladeStage{ this }});

		addStage(shared<WaitStage>{new WaitStage{ this, 3.f }});
		addStage(shared<UfoStage>{new UfoStage{ this }});

		addStage(shared<WaitStage>{new WaitStage{ this, 3.f }});
		addStage(shared<HexagonStage>{new HexagonStage{ this }});

		addStage(shared<WaitStage>{new WaitStage{ this, 3.f }});
		addStage(shared<VanguardStage>{new VanguardStage{ this }});

		addStage(shared<WaitStage>{new WaitStage{ this, 3.f }});
		addStage(shared<UfoStage>{new UfoStage{ this }});

		addStage(shared<WaitStage>{new WaitStage{ this, 5.f }});
		addStage(shared<TwinBladeStage>{new TwinBladeStage{ this }});

		addStage(shared<WaitStage>{new WaitStage{ this, 5.f }});
		addStage(shared<ChaosStage>{new ChaosStage{ this }});

		addStage(shared<WaitStage>{new WaitStage{ this, 7.f }});
		addStage(shared<BossStage>{new BossStage{ this }});
	}

	void GameLevelOne::GameOver()
	{
		mGamePlayHUD.lock()->gameFinished(false);
	}

	void GameLevelOne::spawnCosmetics()
	{
		auto backDropActor = spawnActor<BackDropActor>("SpaceShooterRedux/Backgrounds/darkPurple.png");
		weak<BackGroundLayer> planets = spawnActor<BackGroundLayer>();
		planets.lock()->setAssets(
			{
				"SpaceShooterRedux/PNG/Planets/Planet1.png",
				"SpaceShooterRedux/PNG/Planets/Planet2.png",
				"SpaceShooterRedux/PNG/Planets/Planet3.png",
				"SpaceShooterRedux/PNG/Planets/Planet4.png",
				"SpaceShooterRedux/PNG/Planets/Planet5.png",
				"SpaceShooterRedux/PNG/Planets/Planet6.png",
				"SpaceShooterRedux/PNG/Planets/Planet7.png",
			}
		);

		planets.lock()->setSizes(1.f, 1.5f);
		planets.lock()->setSpriteCount(1);
		planets.lock()->setVelocities({0.f, 30.f}, {0.f, 80.f});

		weak<BackGroundLayer> meteors = spawnActor<BackGroundLayer>();
		meteors.lock()->setAssets(
			{
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_big1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_big2.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_big3.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_big4.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_med1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_med3.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_small1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_small2.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_tiny1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorBrown_tiny2.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_big1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_big2.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_big3.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_big4.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_med1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_med2.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_small1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_small2.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_tiny1.png",
				"SpaceShooterRedux/PNG/Meteors/meteorGrey_tiny2.png",
			}
		);

		meteors.lock()->setSizes(0.2f, 0.5f);
		meteors.lock()->setSpriteCount(20);
	}

	void GameLevelOne::AllGameStageFinished()
	{
		mGamePlayHUD.lock()->gameFinished(true);
	}

	void GameLevelOne::QuitGame()
	{
		getApplication()->quitApplication();
	}

	void GameLevelOne::RestartGame()
	{
		PlayerManager::get().reset();
		getApplication()->loadWorld<GameLevelOne>();
	}
}