#pragma once
#include <SFML/Graphics.hpp>
#include <box2d/b2_body.h>
#include "object.h"
#include "core.h"
#include "framework/delegate.h"

class b2Body;
namespace ly
{
	class World; //The owner of Actor class is World
	class Actor : public Object //Actor holds a pointer to World and is a child class of object
	{
	public:
		Actor(World* owningWorld, const std::string& texturePath = "");
		virtual ~Actor();
		void BeginPlayInternal();
		void TickInternal(float deltaTime);
		virtual void BeginPlay(); //So that it can be overrided by the owner class's BeginPlay function
		virtual void Tick(float deltaTime);
		void setTexture(std::string texturePath);
		virtual void Render(sf::RenderWindow& window) const;
		void setActorLocation(const sf::Vector2f& newLocation);
		void setActorRotation(float newRotation);
		void addActorLocationOffset(const sf::Vector2f& offsetAmt);
		void addActorRotationOffset(const float offsetAmt);
		sf::Vector2f getActorLocation() const;
		float getActorRotation() const;
		sf::Vector2f getActorForwardDirection() const;
		sf::Vector2f getActorRightDirection() const;
		sf::Vector2u getWindowSize() const;
		sf::FloatRect getActorGlobalBounds() const;

		const World* getWorld() const { return mOwningWorld; }
		World* getWorld() { return mOwningWorld; }
		bool isActorOutOfWindowBounds(float allowance = 10.f) const;
		void setEnablePhysics(bool enable);
		virtual void onActorBeginOverlap(Actor* other);
		virtual void onActorEndOverlap(Actor* other);
		virtual void Destroy() override;

		static uint8 getNeutralTeamID() { return neutralTeamID; }
		void setTeamID(uint8 teamID) { mTeamID = teamID; }

		uint8 getTeamID() const { return mTeamID; }
		bool isOtherHostile(Actor* other) const;
		virtual void applyDamage(float amt);

		sf::Sprite& getSprite() { return mSprite; }
		const sf::Sprite& getSprite() const { return mSprite; }

		Delegate<Actor*> onActorDestroy;
		void setTextureRepeated(bool repeated);
	private:
		void initializePhysics();
		void unInitializePhysics();
		void updatePhysicsBodyTransform();
		void centerPivot();
		World* mOwningWorld{};
		bool mHasBeganPlay;

		sf::Sprite mSprite;
		shared<sf::Texture> mTexture;

		b2Body* mPhysicsBody;
		bool mPhysicsEnabled;
		uint8 mTeamID;
		const static uint8 neutralTeamID = 255;
	};
}