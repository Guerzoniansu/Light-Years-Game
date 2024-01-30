#pragma once
#include "framework/actor.h"
#include "gameplay/health.h"
//#include "framework/AssetManager.h"

namespace ly
{
	class SpaceShip :public Actor
	{
	public:
		SpaceShip(World* owningWorld, const std::string& texturePath = "");
		virtual void Tick(float deltaTime) override;
		void setVelocity(const sf::Vector2f& newVelocity);
		sf::Vector2f getVelocity() const;
		virtual void shoot();
		virtual void BeginPlay() override;
		virtual void applyDamage(float amt) override;

		Health& getHealthComp() { return mHealthComp; };
	private:
		void Blink();
		void updateBlink(float deltaTime);
		virtual void OnHealthChanged(float amt, float health, float maxHealth);
		virtual void OnTakenDamage(float amt, float health, float maxHealth);
		virtual void Blow();

		virtual void Blew();

		sf::Vector2f mVelocity;
		Health mHealthComp;

		float mBlinkTime;
		float mBlinkDuration;
		sf::Color mBlinkColorOffset;
	};
}