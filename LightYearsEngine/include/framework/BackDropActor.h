#pragma once
#include "framework/actor.h"

namespace ly
{
	class BackDropActor : public Actor
	{
	public:
		BackDropActor(World* world, const std::string& texturePath, const sf::Vector2f& movingVelocity = sf::Vector2f{0.f, -50.f});
		virtual void Tick(float deltaTime) override;

	private:
		sf::Vector2f mMovingVelocity;
		float mLeftShift;
		float mTopShift;
	};
}