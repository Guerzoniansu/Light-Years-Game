#include "SpaceShip/spaceship.h"
#include "framework/actor.h"
#include "framework/math.h"
#include "VFX/explosion.h"

namespace ly
{
	SpaceShip::SpaceShip(World* owningWorld, const std::string& texturePath)
		:Actor{ owningWorld, texturePath },
		mVelocity{},
		mHealthComp{ 100.f, 100.f },
		mBlinkTime{ 0 },
		mBlinkDuration{ 0.2f },
		mBlinkColorOffset{255, 0, 0, 255}
	{

	}
	void SpaceShip::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		addActorLocationOffset(getVelocity() * deltaTime);
		updateBlink(deltaTime);
	}
	void SpaceShip::setVelocity(const sf::Vector2f& newVelocity)
	{
		mVelocity = newVelocity;
	}
	sf::Vector2f SpaceShip::getVelocity() const
	{
		return mVelocity;
	}
	void SpaceShip::shoot()
	{

	}
	void SpaceShip::BeginPlay()
	{
		Actor::BeginPlay();
		setEnablePhysics(true);
		mHealthComp.onHealthChanged.bindAction(getWeakRef(), &SpaceShip::OnHealthChanged);
		mHealthComp.onTakenDamage.bindAction(getWeakRef(), &SpaceShip::OnTakenDamage);
		mHealthComp.onHealthEmpty.bindAction(getWeakRef(), &SpaceShip::Blow);
	}
	void SpaceShip::applyDamage(float amt)
	{
		mHealthComp.changeHealth(-amt);
	}
	void SpaceShip::Blink()
	{
		if (mBlinkTime == 0.f)
		{
			mBlinkTime = mBlinkDuration;
		}
	}
	void SpaceShip::updateBlink(float deltaTime)
	{
		if (mBlinkTime > 0)
		{
			mBlinkTime -= deltaTime;
			mBlinkTime = mBlinkTime > 0 ? mBlinkTime : 0.f;

			getSprite().setColor(lerpColor(sf::Color::White, mBlinkColorOffset, mBlinkTime));
		}
	}
	void SpaceShip::OnHealthChanged(float amt, float health, float maxHealth)
	{
		
	}
	void SpaceShip::OnTakenDamage(float amt, float health, float maxHealth)
	{
		Blink();
	}
	void SpaceShip::Blow()
	{
		Explosion* exp = new Explosion();
		exp->spawnExplosion(getWorld(), getActorLocation());
		Blew();
		Destroy();
		delete exp;
	}
	void SpaceShip::Blew()
	{

	}
}