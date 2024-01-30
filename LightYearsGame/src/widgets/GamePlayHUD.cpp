#include "widgets/GamePlayHUD.h"
#include "Player/PlayerManager.h"
#include "Player/playerSpaceship.h"
#include "Player/player.h"
#include "framework/actor.h"

namespace ly
{
	GamePlayHUD::GamePlayHUD()
		:mFrameRateText{"Frame Rate: "},
		mPlayerHealthBar{},
		mPlayerLifeIcon{"SpaceShooterRedux/PNG/UI/playerLife1_blue.png"},
		mPlayerLifeText{""},
		mPlayerScoreIcon{ "SpaceShooterRedux/PNG/Power-ups/star_gold.png" },
		mPlayerScoreText{ "" },
		mHealthyGuageBarColor{128, 255, 125, 255},
		mCriticalGuageBarColor{255, 0, 0, 255},
		mCriticalThreshold{0.3f},
		mWidgetSpacing{10.f},
		mWinLoseText{""},
		mFinalScoreText{""},
		mRestartButton{"Restart"},
		mQuitButton{"Quit"},
		mWindowSize{}
	{
		mFrameRateText.setTextSize(16);
		mPlayerLifeText.setTextSize(16);
		mPlayerScoreText.setTextSize(16);

		mWinLoseText.setVisibility(false);
		mFinalScoreText.setVisibility(false);
		mRestartButton.setVisibility(false);
		mQuitButton.setVisibility(false);

		mWinLoseText.setTextSize(40);
		mFinalScoreText.setTextSize(30);
	}

	void GamePlayHUD::draw(sf::RenderWindow& windowRef)
	{
		mWindowSize = windowRef.getSize();
		mFrameRateText.NativeDraw(windowRef);
		mPlayerHealthBar.NativeDraw(windowRef);
		mPlayerLifeIcon.NativeDraw(windowRef);
		mPlayerLifeText.NativeDraw(windowRef);
		mPlayerScoreIcon.NativeDraw(windowRef);
		mPlayerScoreText.NativeDraw(windowRef);

		mWinLoseText.NativeDraw(windowRef);
		mFinalScoreText.NativeDraw(windowRef);
		mRestartButton.NativeDraw(windowRef);
		mQuitButton.NativeDraw(windowRef);
	}

	void GamePlayHUD::Tick(float deltaTime)
	{
		int frameRate = (int)(1.f / deltaTime);
		std::string frameRateText = "Frame Rate: " + std::to_string(frameRate);
		mFrameRateText.setString(frameRateText);
	}

	bool GamePlayHUD::handleEvent(const sf::Event& event)
	{
		if (mRestartButton.handleEvent(event))
		{
			return true;
		}
		if (mQuitButton.handleEvent(event))
		{
			return true;
		}
		return HUD::handleEvent(event);
	}
	void GamePlayHUD::init(const sf::RenderWindow& windowRef)
	{
		auto windowSize = windowRef.getSize();
		mWindowSize = windowSize;
		mPlayerHealthBar.setWidgetLocation(sf::Vector2f{ 20.f, (float)(windowSize.y - 50.f) });
		
		sf::Vector2f nextWidgetPos = mPlayerHealthBar.getWidgetLocation();
		nextWidgetPos += sf::Vector2f{ mPlayerHealthBar.getBound().width + mWidgetSpacing, 0.f };
		mPlayerLifeIcon.setWidgetLocation(nextWidgetPos);

		nextWidgetPos += sf::Vector2f{ mPlayerLifeIcon.getBound().width + mWidgetSpacing, 0.f };
		mPlayerLifeText.setWidgetLocation(nextWidgetPos);

		nextWidgetPos += sf::Vector2f{ mPlayerLifeText.getBound().width + mWidgetSpacing * 4, 0.f };
		mPlayerScoreIcon.setWidgetLocation(nextWidgetPos);

		nextWidgetPos += sf::Vector2f{ mPlayerScoreIcon.getBound().width + mWidgetSpacing, 0.f };
		mPlayerScoreText.setWidgetLocation(nextWidgetPos);

		mWinLoseText.setWidgetLocation({ windowSize.x / 2.f - mWinLoseText.getBound().width / 2.f, 100.f });
		mFinalScoreText.setWidgetLocation({ windowSize.x / 2.f - mFinalScoreText.getBound().width / 2.f, 200.f });

		mRestartButton.setWidgetLocation({ windowSize.x / 2.f - mRestartButton.getBound().width / 2.f, windowSize.y / 2.f });
		mQuitButton.setWidgetLocation(mRestartButton.getWidgetLocation() + sf::Vector2f{ 0.f, 50.f });

		mRestartButton.onButtonClicked.bindAction(getWeakRef(), &GamePlayHUD::restartButtonClicked);
		mQuitButton.onButtonClicked.bindAction(getWeakRef(), &GamePlayHUD::quitButtonClicked);

		refreshHealthBar();
		connectPlayerStatus();

	}

	void GamePlayHUD::playerHeathUpdated(float amt, float currentHealth, float maxHealth)
	{
		mPlayerHealthBar.updateValue(currentHealth, maxHealth);
		if (currentHealth/maxHealth < mCriticalThreshold)
		{
			mPlayerHealthBar.setForeGroundColor(mCriticalGuageBarColor);
		}
		else
		{
			mPlayerHealthBar.setForeGroundColor(mHealthyGuageBarColor);
		}
	}

	void GamePlayHUD::playerScoreUpdated(int newScore)
	{
		mPlayerScoreText.setString(std::to_string(newScore));
	}

	void GamePlayHUD::playerLifeCountUpdated(int newLifeCount)
	{
		mPlayerLifeText.setString(std::to_string(newLifeCount));
	}

	void GamePlayHUD::playerSpaceShipDestroyed(Actor* actor)
	{
		refreshHealthBar();
		mPlayerHealthBar.setForeGroundColor(mHealthyGuageBarColor);
	}

	void GamePlayHUD::refreshHealthBar()
	{
		Player* player = PlayerManager::get().getPlayer();

		if (player && !player->getCurrentSpaceShip().expired())
		{
			weak<PlayerSpaceShip> playerSpaceShip = player->getCurrentSpaceShip();
			playerSpaceShip.lock()->onActorDestroy.bindAction(getWeakRef(), &GamePlayHUD::playerSpaceShipDestroyed);
			Health& healthComp = player->getCurrentSpaceShip().lock()->getHealthComp();
			healthComp.onHealthChanged.bindAction(getWeakRef(), &GamePlayHUD::playerHeathUpdated);
			mPlayerHealthBar.updateValue(healthComp.getHealth(), healthComp.getMaxHealth());
		}
	}

	void GamePlayHUD::connectPlayerStatus()
	{
		Player* player = PlayerManager::get().getPlayer();

		if (player)
		{
			unsigned int lifeLeft = player->getLifeCount();
			mPlayerLifeText.setString(std::to_string(lifeLeft));
			player->onLifeChange.bindAction(getWeakRef(), &GamePlayHUD::playerLifeCountUpdated);

			int playerScore = player->getScore();
			mPlayerScoreText.setString(std::to_string(playerScore));
			player->onScoreChange.bindAction(getWeakRef(), &GamePlayHUD::playerScoreUpdated);
		}
	}

	void GamePlayHUD::gameFinished(bool playerWon)
	{
		mWinLoseText.setVisibility(true);
		mFinalScoreText.setVisibility(true);
		mRestartButton.setVisibility(true);
		mQuitButton.setVisibility(true);

		int score = PlayerManager::get().getPlayer()->getScore();

		mFinalScoreText.setString("Score: " + std::to_string(score));

		if (playerWon)
		{
			mWinLoseText.setString("You Win!");
		}
		else
		{
			mWinLoseText.setString("You Lose!");
		}
		mWinLoseText.setWidgetLocation({ mWindowSize.x / 2.f - mWinLoseText.getBound().width / 2.f, 100.f });
		mFinalScoreText.setWidgetLocation({ mWindowSize.x / 2.f - mFinalScoreText.getBound().width / 2.f, 200.f });
	}

	void GamePlayHUD::restartButtonClicked()
	{
		onRestartButtonClicked.broadCast();
	}

	void GamePlayHUD::quitButtonClicked()
	{
		onQuitButtonClicked.broadCast();
	}
}