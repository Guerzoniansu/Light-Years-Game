#pragma once
#include <SFML/Graphics.hpp>
#include "widgets/widget.h"

namespace ly
{
	class ImageWidget : public Widget
	{
	public:
		ImageWidget(const std::string& imagePath);
		void setImage(const shared<sf::Texture>& newTexture);

		virtual sf::FloatRect getBound() const;

	private:
		virtual void locationUpdated(const sf::Vector2f& newLocation) override;
		virtual void rotationUpdated(float newRotation) override;
		virtual void draw(sf::RenderWindow& windowRef) override;
		shared<sf::Texture> mTexture;
		sf::Sprite mSprite;
	};
}