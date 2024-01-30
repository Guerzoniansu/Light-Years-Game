#include "framework/BackGroundLayer.h"
#include "framework/AssetManager.h"
#include "framework/math.h"
#include "framework/world.h"

namespace ly
{
	BackGroundLayer::BackGroundLayer(World* world,
		const list<std::string>& assetPaths,
		const sf::Vector2f minVelocity,
		const sf::Vector2f maxVelocity,
		float sizeMin, float sizeMax, int spriteCount,
		const sf::Color& tintColor
	)
		:Actor{world},
		mMinVelocity{minVelocity},
		mMaxVelocity{maxVelocity},
		mSizeMin{sizeMin},
		mSizeMax{sizeMax},
		mSpriteCount{spriteCount},
		mTintColor{tintColor}
	{
		setAssets(assetPaths);
		setEnablePhysics(false);
	}
	void BackGroundLayer::setAssets(const list<std::string>& assetPath)
	{
		for (const std::string& texturePath : assetPath)
		{
			shared<sf::Texture> newTexture = AssetManager::Get().LoadTexture(texturePath);
			mTextures.push_back(newTexture);
		}
		refreshSprite();
	}
	void BackGroundLayer::refreshSprite()
	{
		mSprites.clear();
		mVelocities.clear();

		for (int i = 0; i < mSpriteCount; i++)
		{
			sf::Sprite newSprite{};
			randomSpriteTexture(newSprite);
			randomSpriteTransform(newSprite, true);
			mSprites.push_back(newSprite);

			float velocityX = randomRange(mMinVelocity.x, mMaxVelocity.x);
			float velocityY = randomRange(mMinVelocity.y, mMaxVelocity.y);

			mVelocities.push_back(sf::Vector2f{ velocityX, velocityY });
		}

		setColorTint(mTintColor);
	}
	void BackGroundLayer::randomSpriteTexture(sf::Sprite& sprite)
	{
		if (mTextures.size() > 0)
		{
			shared<sf::Texture> pickedTexture = getRandomTexture();
			sprite.setTexture(*(pickedTexture.get()));
			sprite.setTextureRect(sf::IntRect{ 0, 0, (int)pickedTexture->getSize().x, (int)pickedTexture->getSize().y });
			sf::FloatRect bound = getActorGlobalBounds();
			sprite.setOrigin(bound.width / 2.f, bound.height / 2.f);
		}
	}
	void BackGroundLayer::randomSpriteTransform(sf::Sprite& sprite, bool randomY)
	{
		randomSpritePosition(sprite, randomY);
		randomSpriteRotation(sprite);
		randomSpriteSize(sprite);
	}
	void BackGroundLayer::randomSpritePosition(sf::Sprite& sprite, bool randomY)
	{
		auto windowSize = getWorld()->getWindowSize();
		auto bound = sprite.getGlobalBounds();
		float posX = randomRange(0.f, windowSize.x);
		float posY = randomY ? randomRange(0.f, windowSize.y) : -bound.height;

		sprite.setPosition(sf::Vector2f{ posX, posY });
	}
	void BackGroundLayer::randomSpriteRotation(sf::Sprite& sprite)
	{
		sprite.setRotation(randomRange(0.f, 360.f));
	}
	void BackGroundLayer::randomSpriteSize(sf::Sprite& sprite)
	{
		float size = randomRange(mSizeMin, mSizeMax);
		sprite.setScale(size, size);
	}
	bool BackGroundLayer::isSpriteOffScreen(sf::Sprite& sprite) const
	{
		auto bound = sprite.getGlobalBounds();
		auto windowSize = getWorld()->getWindowSize();
		auto spritePos = sprite.getPosition();

		if (spritePos.x < -bound.width || spritePos.x >windowSize.x + bound.width)
		{
			return true;
		}
		if (spritePos.y < -bound.height || spritePos.y >windowSize.y + bound.height)
		{
			return true;
		}

		return false;
	}
	void BackGroundLayer::setColorTint(const sf::Color& color)
	{
		mTintColor = color;
		for (sf::Sprite& sprite : mSprites)
		{
			sprite.setColor(color);
		}
	}
	void BackGroundLayer::setSpriteCount(int count)
	{
		mSpriteCount = count;
		refreshSprite();
	}
	void BackGroundLayer::setVelocities(const sf::Vector2f& minVel, const sf::Vector2f& maxVel)
	{
		mMinVelocity = minVel;
		mMaxVelocity = maxVel;

		for (int i = 0; i < mVelocities.size(); i++)
		{
			float velocityX = randomRange(mMinVelocity.x, mMaxVelocity.x);
			float velocityY = randomRange(mMinVelocity.y, mMaxVelocity.y);

			mVelocities[i] = sf::Vector2f{ velocityX, velocityY };
		}
	}
	void BackGroundLayer::setSizes(float min, float max)
	{
		mSizeMin = min;
		mSizeMax = max;

		for (int i = 0; i < mSprites.size(); i++)
		{
			randomSpriteSize(mSprites[i]);
		}
	}
	void BackGroundLayer::Tick(float deltaTime)
	{
		Actor::Tick(deltaTime);
		for (int i = 0; i < mSprites.size(); i++)
		{
			sf::Sprite& sprite = mSprites[i];
			sf::Vector2f& vel = mVelocities[i];

			sprite.setPosition(sprite.getPosition() + vel * deltaTime);
			if (isSpriteOffScreen(sprite))
			{
				randomSpriteTransform(sprite);
				randomSpriteTexture(sprite);
				float velocityX = randomRange(mMinVelocity.x, mMaxVelocity.x);
				float velocityY = randomRange(mMinVelocity.y, mMaxVelocity.y);

				mVelocities[i] = sf::Vector2f{ velocityX, velocityY };
			}
		}
	}
	void BackGroundLayer::Render(sf::RenderWindow& window) const
	{
		Actor::Render(window);
		for (const sf::Sprite& sprite : mSprites)
		{
			window.draw(sprite);
		}
	}
	shared<sf::Texture> BackGroundLayer::getRandomTexture() const
	{
		int randomPickIndex = (int)randomRange(0.f, mTextures.size());
		return mTextures[randomPickIndex];
	}
}