#include "widgets/ImageWidget.h"
#include "framework/AssetManager.h"

namespace ly
{
	ImageWidget::ImageWidget(const std::string& imagePath)
		: mTexture{AssetManager::Get().LoadTexture(imagePath)},
		mSprite{ *(mTexture.get()) }
	{

	}
	void ImageWidget::setImage(const shared<sf::Texture>& newTexture)
	{
		if (newTexture)
		{
			mTexture = newTexture;
			mSprite.setTexture(*(mTexture.get()));
		}
	}
	sf::FloatRect ImageWidget::getBound() const
	{
		return mSprite.getGlobalBounds();
	}
	void ImageWidget::locationUpdated(const sf::Vector2f& newLocation)
	{
		mSprite.setPosition(newLocation);
	}
	void ImageWidget::rotationUpdated(float newRotation)
	{
		mSprite.setRotation(newRotation);
	}
	void ImageWidget::draw(sf::RenderWindow& windowRef)
	{
		windowRef.draw(mSprite);
	}
}