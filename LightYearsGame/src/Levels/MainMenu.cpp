#include "Levels/MainMenu.h"
#include "widgets/MainMenuHUD.h"
#include "framework/application.h"
#include "Levels/levelone.h"
#include "framework/BackDropActor.h"

namespace ly
{
	MainMenu::MainMenu(Application* owningApp)
		:World{owningApp}
	{
		mMainMenuHUD = spawnHUD<MainMenuHUD>();
	}

	void MainMenu::BeginPlay()
	{
		mMainMenuHUD.lock()->onStartButtonClicked.bindAction(getWeakRef(), &MainMenu::startGame);
		mMainMenuHUD.lock()->onQuitButtonClicked.bindAction(getWeakRef(), &MainMenu::quitGame);
		spawnActor<BackDropActor>("SpaceShooterRedux/mainMenuBg.png", sf::Vector2f{0.f, 0.f});
	}
	void MainMenu::startGame()
	{
		getApplication()->loadWorld<GameLevelOne>();
	}
	void MainMenu::quitGame()
	{
		getApplication()->quitApplication();
	}
}