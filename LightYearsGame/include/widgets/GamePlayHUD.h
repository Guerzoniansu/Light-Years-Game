#pragma once
#include "widgets/HUD.h"
#include "widgets/TextWidget.h"
#include "widgets/ImageWidget.h"
#include "widgets/guage.h"
#include "framework/actor.h"
#include "widgets/button.h"

namespace ly
{
	class GamePlayHUD: public HUD
	{
	public:
		GamePlayHUD();
		virtual void draw(sf::RenderWindow& windowRef) override;

		virtual void Tick(float deltaTime) override;
		virtual bool handleEvent(const sf::Event& event) override;

		void gameFinished(bool playerWon);
		Delegate<> onRestartButtonClicked;
		Delegate<> onQuitButtonClicked;

	private:
		virtual void init(const sf::RenderWindow& windowRef) override;
		void playerHeathUpdated(float amt, float currentHealth, float maxHealth);
		void playerScoreUpdated(int newScore);
		void playerSpaceShipDestroyed(Actor* actor);
		void refreshHealthBar();
		void connectPlayerStatus();
		void playerLifeCountUpdated(int newLifeCount);

		void restartButtonClicked();
		void quitButtonClicked();

		TextWidget mFrameRateText;
		float previousFrameTime;
		HealthBar mPlayerHealthBar;

		ImageWidget mPlayerLifeIcon;
		TextWidget mPlayerLifeText;

		ImageWidget mPlayerScoreIcon;
		TextWidget mPlayerScoreText;

		TextWidget mWinLoseText;
		TextWidget mFinalScoreText;
		Button mRestartButton;
		Button mQuitButton;

		sf::Color mHealthyGuageBarColor;
		sf::Color mCriticalGuageBarColor;

		float mCriticalThreshold;
		float mWidgetSpacing;

		sf::Vector2u mWindowSize;

	};
}