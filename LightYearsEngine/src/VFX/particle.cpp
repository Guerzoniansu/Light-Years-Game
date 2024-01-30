#include "VFX/particle.h"
#include "framework/math.h"

namespace ly
{
	Particle::Particle(World* owningWorld, const std::string& texturePath)
		:Actor{owningWorld, texturePath},
		mVelocity{},
		mLifeTime{1.f},
		mTimer{}
	{

	}
	void Particle::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);

		Move(deltaTime);
		Fade(deltaTime);

		if (mTimer.getElapsedTime().asSeconds() >= mLifeTime)
		{
			Destroy();
		}
	}
	void Particle::RandomVelocity(float minSpeed, float maxSpeed)
	{
		mVelocity = RandomUnitVector() * randomRange(minSpeed, maxSpeed);
	}
	void Particle::RandomSize(float min, float max)
	{
		float randScale = randomRange(min, max);
		getSprite().setScale(randScale, randScale);
	}
	void Particle::RandomLifeTime(float min, float max)
	{
		mLifeTime = randomRange(min, max);
	}
	void Particle::Move(float deltaTime)
	{
		addActorLocationOffset(mVelocity * deltaTime);
	}
	void Particle::Fade(float deltaTime)
	{
		float elapsedTime = mTimer.getElapsedTime().asSeconds();
		getSprite().setColor(lerpColor(getSprite().getColor(), sf::Color(255, 255, 255, 0), elapsedTime/mLifeTime));
		getSprite().setScale(lerpVector(getSprite().getScale(), sf::Vector2f{ 0,0 }, elapsedTime / mLifeTime));
	}
}