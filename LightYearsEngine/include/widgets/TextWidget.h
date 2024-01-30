#pragma once
#include <SFML/Graphics.hpp>

#include "framework/core.h"
#include "widgets/widget.h"

namespace ly
{
	class TextWidget : public Widget
	{
	public:
		TextWidget(const std::string& textStr,
			const std::string& fontPath = "SpaceShooterRedux/Bonus/kenvector_future.ttf",
			unsigned int characterSize = 10
		);

		void setString(const std::string& newStr);
		void setTextSize(unsigned int newTextSize);
		virtual sf::FloatRect getBound() const override;

	private:
		virtual void locationUpdated(const sf::Vector2f& newLoc) override;
		virtual void rotationUpdated(float newRot) override;
		virtual void draw(sf::RenderWindow& windowRef) override;
		shared<sf::Font> mFont;
		sf::Text mText;
	};
}