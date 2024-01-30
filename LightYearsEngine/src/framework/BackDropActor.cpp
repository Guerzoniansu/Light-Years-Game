#include "framework/BackDropActor.h"
#include "framework/world.h"

namespace ly
{
	BackDropActor::BackDropActor(World* world, const std::string& texturePath, const sf::Vector2f& movingVelocity)
		: Actor{ world,texturePath },
		mMovingVelocity{ movingVelocity },
		mLeftShift{ 0.f },
		mTopShift{0.f}
	{
		auto windowSize = world->getWindowSize();
		getSprite().setOrigin({ 0.f, 0.f });
		getSprite().setTextureRect(sf::IntRect{sf::Vector2i{0, 0}, sf::Vector2i{(int)windowSize.x, (int)windowSize.y}});

		setTextureRepeated(true);
	}
	void BackDropActor::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		mLeftShift += deltaTime * mMovingVelocity.x;
		mTopShift += deltaTime * mMovingVelocity.y;
		
		sf::IntRect currentRect = getSprite().getTextureRect();
		currentRect.left = mLeftShift;
		currentRect.top = mTopShift;

		getSprite().setTextureRect(currentRect);
	}
}