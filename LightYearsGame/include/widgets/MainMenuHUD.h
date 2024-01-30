#pragma once
#include "widgets/HUD.h"
#include "widgets/button.h"
#include "widgets/TextWidget.h"

namespace ly
{
	class MainMenuHUD : public HUD
	{
	public:
		MainMenuHUD();
		virtual void draw(sf::RenderWindow& windowRef) override;
		virtual bool handleEvent(const sf::Event& event) override;

		Delegate<> onStartButtonClicked;
		Delegate<> onQuitButtonClicked;

	private:
		virtual void init(const sf::RenderWindow& windowRef) override;

		TextWidget mTitleText;

		Button mStartButton;
		Button mQuitButton;

		void startButtonClicked();
		void quitButtonClicked();
	};
}