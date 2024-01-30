#include <SFML/Graphics.hpp>
#include <box2d/b2_body.h>

#include "framework/actor.h"
#include "framework/core.h"
#include "framework/AssetManager.h"
#include "framework/math.h"
#include "framework/world.h"
#include "framework/physics.h"

namespace ly
{
	Actor::Actor(World* owningWorld, const std::string& texturePath)
		:mOwningWorld{ owningWorld },
		mHasBeganPlay{ false },
		mSprite{},
		mTexture{},
		mPhysicsBody{ nullptr },
		mPhysicsEnabled{ false },
		mTeamID{ getNeutralTeamID()}
	{
		setTexture(texturePath);
	}
	Actor::~Actor()
	{
		
	}
	void Actor::BeginPlayInternal()
	{
		if (!mHasBeganPlay)
		{
			mHasBeganPlay = true;
			BeginPlay();
		}
	}
	void Actor::TickInternal(float deltaTime)
	{
		if (!IsPendingDestroy())
		{
			Tick(deltaTime);
		}
	}
	void Actor::BeginPlay() //It will be overwritten by the world's BeginPlay function
	{
		//LOG("Actor began play");
	}
	void Actor::Tick(float deltaTime)
	{
		//LOG("Actor ticking");
	}
	void Actor::setTexture(std::string texturePath)
	{
		mTexture = AssetManager::Get().LoadTexture(texturePath);
		if (!mTexture) return;
		mSprite.setTexture(*mTexture);

		int textureWidth = mTexture->getSize().x;
		int textureHeight = mTexture->getSize().y;
		mSprite.setTextureRect(sf::IntRect{ sf::Vector2i{}, sf::Vector2i{textureWidth, textureHeight} });
		centerPivot();
	}
	void Actor::Render(sf::RenderWindow& window) const
	{
		if (IsPendingDestroy())
		{
			return;
		}
		window.draw(mSprite);
	}
	void Actor::setActorLocation(const sf::Vector2f& newLocation)
	{
		mSprite.setPosition(newLocation);
		updatePhysicsBodyTransform();
	}
	void Actor::setActorRotation(float newRotation)
	{
		mSprite.setRotation(newRotation);
		updatePhysicsBodyTransform();
	}
	void Actor::addActorLocationOffset(const sf::Vector2f& offsetAmt)
	{
		setActorLocation(getActorLocation() + offsetAmt);
	}
	void Actor::addActorRotationOffset(const float offsetAmt)
	{
		setActorRotation(getActorRotation() + offsetAmt);
	}
	sf::Vector2f Actor::getActorLocation() const
	{
		return mSprite.getPosition();
	}
	float Actor::getActorRotation() const
	{
		return mSprite.getRotation();
	}
	sf::Vector2f Actor::getActorForwardDirection() const
	{
		return rotationToVector(getActorRotation() + 180.f);
	}
	sf::Vector2f Actor::getActorRightDirection() const
	{
		return rotationToVector(getActorRotation() + 90.f);
	}
	void Actor::centerPivot()
	{
		sf::FloatRect bound = mSprite.getGlobalBounds();
		mSprite.setOrigin(bound.width / 2.f, bound.height / 2.f);
	}
	sf::Vector2u Actor::getWindowSize() const
	{
		return mOwningWorld->getWindowSize();
	}
	sf::FloatRect Actor::getActorGlobalBounds() const
	{
		return mSprite.getGlobalBounds();
	}
	bool Actor::isActorOutOfWindowBounds(float allowance) const
	{
		float windowWidth = getWorld()->getWindowSize().x;
		float windowHeight = getWorld()->getWindowSize().y;

		sf::Vector2f actorPos = getActorLocation();
		if (actorPos.x < -allowance)
		{
			return true;
		}
		if (actorPos.x > windowWidth + allowance)
		{
			return true;
		}
		if (actorPos.y < -allowance)
		{
			return true;
		}
		if (actorPos.y > windowHeight + allowance)
		{
			return true;
		}
		return false;
	}
	void Actor::setEnablePhysics(bool enable)
	{
		mPhysicsEnabled = enable;
		if (mPhysicsEnabled)
		{
			initializePhysics();
		}
		else
		{
			unInitializePhysics();
		}
	}
	void Actor::initializePhysics()
	{
		if (!mPhysicsBody)
		{
			mPhysicsBody = Physics::get().addListener(this);
		}
	}
	void Actor::unInitializePhysics()
	{
		if (mPhysicsBody)
		{
			Physics::get().removeListener(mPhysicsBody);
			mPhysicsBody = nullptr;
		}
	}
	void Actor::updatePhysicsBodyTransform()
	{
		if (mPhysicsBody)
		{
			float physicsScale = Physics::get().getPhysicsScale();
			b2Vec2 pos{ getActorLocation().x * physicsScale, getActorLocation().y * physicsScale };
			float rotation = degreesToRadians(getActorRotation());

			mPhysicsBody->SetTransform(pos, rotation);
		}
	}
	void Actor::onActorBeginOverlap(Actor* other)
	{
		
	}
	void Actor::onActorEndOverlap(Actor* other)
	{
		
	}
	void Actor::Destroy()
	{
		unInitializePhysics();
		onActorDestroy.broadCast(this);
		Object::Destroy();
	}

	bool Actor::isOtherHostile(Actor* other) const
	{
		if (other == nullptr)
		{
			return false;
		}
		if (getTeamID() == getNeutralTeamID() || other->getTeamID() == getNeutralTeamID())
		{
			return false;
		}
		return getTeamID() != other->getTeamID();
	}
	void Actor::applyDamage(float amt)
	{

	}

	void Actor::setTextureRepeated(bool repeated)
	{
		mTexture->setRepeated(true);
	}
}