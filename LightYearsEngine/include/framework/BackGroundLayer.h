#pragma once
#include "framework/actor.h"

namespace ly
{
	class BackGroundLayer : public Actor
	{
	public:
		BackGroundLayer(World* world,
			const list<std::string>& assetPaths = {},
			const sf::Vector2f minVelocity = sf::Vector2f{ 0.f, 50.f },
			const sf::Vector2f maxVelocity = sf::Vector2f{ 0.f, 200.f },
			float sizeMin = 1.f,
			float sizeMax = 2.f,
			int spriteCount = 20,
			const sf::Color& tintColor = sf::Color{180, 180, 200, 255}
		);

		void setAssets(const list<std::string>& assetPath);
		void setColorTint(const sf::Color& color);
		void setSpriteCount(int count);

		void setVelocities(const sf::Vector2f& minVel, const sf::Vector2f& maxVel);
		void setSizes(float min, float max);

		virtual void Tick(float deltaTime) override;
		virtual void Render(sf::RenderWindow& window) const override;

	private:
		void refreshSprite();
		void randomSpriteTexture(sf::Sprite& sprite);
		void randomSpriteTransform(sf::Sprite& sprite, bool randomY = false);
		void randomSpritePosition(sf::Sprite& sprite, bool randomY);
		void randomSpriteRotation(sf::Sprite& sprite);
		void randomSpriteSize(sf::Sprite& sprite);
		bool isSpriteOffScreen(sf::Sprite& sprite) const;

		shared<sf::Texture> getRandomTexture() const;


		sf::Vector2f mMinVelocity;
		sf::Vector2f mMaxVelocity;

		float mSizeMin;
		float mSizeMax;

		int mSpriteCount;
		sf::Color mTintColor;

		list<sf::Sprite> mSprites;
		list<shared<sf::Texture>> mTextures;
		list<sf::Vector2f> mVelocities;
	};
}