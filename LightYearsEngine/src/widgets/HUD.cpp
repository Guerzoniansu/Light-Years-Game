#include "widgets/HUD.h"

namespace ly
{
	bool HUD::handleEvent(const sf::Event& event)
	{
		return false;
	}
	void HUD::Tick(float deltaTime)
	{

	}
	HUD::HUD()
		:mAlreadyInit{false}
	{
	}

	void HUD::nativeInit(const sf::RenderWindow& windowRef)
	{
		if (!mAlreadyInit)
		{
			mAlreadyInit = true;
			init(windowRef);
		}
	}

	void HUD::init(const sf::RenderWindow& windowRef)
	{
	}
}