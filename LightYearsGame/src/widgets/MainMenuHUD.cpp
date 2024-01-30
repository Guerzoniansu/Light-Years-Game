#include "widgets/MainMenuHUD.h"

namespace ly
{
	MainMenuHUD::MainMenuHUD()
		:mTitleText{"Light Years"},
		mStartButton{"Start"},
		mQuitButton{"Quit"}
	{
		mTitleText.setTextSize(40);
		mStartButton.setTextSize(20);
		mQuitButton.setTextSize(20);
	}

	void MainMenuHUD::draw(sf::RenderWindow& windowRef)
	{
		mTitleText.NativeDraw(windowRef);
		mStartButton.NativeDraw(windowRef);
		mQuitButton.NativeDraw(windowRef);
	}

	bool MainMenuHUD::handleEvent(const sf::Event& event)
	{
		return mStartButton.handleEvent(event) ||
				mQuitButton.handleEvent(event) ||
				HUD::handleEvent(event);
	}

	void MainMenuHUD::init(const sf::RenderWindow& windowRef)
	{
		sf::Vector2u windowSize = windowRef.getSize();
		mTitleText.setWidgetLocation({ windowSize.x / 2.f - mTitleText.getBound().width / 2.f, 100.f});

		mStartButton.setWidgetLocation({ windowSize.x / 2.f - mStartButton.getBound().width / 2.f, windowSize.y / 2.f });
		mQuitButton.setWidgetLocation(mStartButton.getWidgetLocation() + sf::Vector2f{ 0.f, 50.f });

		mStartButton.onButtonClicked.bindAction(getWeakRef(), &MainMenuHUD::startButtonClicked);
		mQuitButton.onButtonClicked.bindAction(getWeakRef(), &MainMenuHUD::quitButtonClicked);
	}

	void MainMenuHUD::startButtonClicked()
	{
		onStartButtonClicked.broadCast();
	}

	void MainMenuHUD::quitButtonClicked()
	{
		onQuitButtonClicked.broadCast();
	}

}