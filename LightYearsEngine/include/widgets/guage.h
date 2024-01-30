#pragma once

#include "widgets/widget.h"

namespace ly
{
	class HealthBar : public Widget
	{
	public:
		HealthBar(const sf::Vector2f& size = sf::Vector2f {150.f, 25.f},
			float initialPercent = 0.75f,
			const sf::Color& foregroundColor = sf::Color{128, 255, 128, 255},
			const sf::Color& backgroundColor = sf::Color{ 128, 128, 128, 255 }
		);
		void updateValue(float value, float maxValue);
		virtual sf::FloatRect getBound() const;

		void setTextSize(unsigned int newTextSize);
		void setForeGroundColor(const sf::Color& color);
		void setBackGroundColor(const sf::Color& color);
	private:
		virtual void draw(sf::RenderWindow& windowRef) override;
		virtual void locationUpdated(const sf::Vector2f& newLoc) override;
		virtual void rotationUpdated(float newRot) override;

		void centerText();

		shared<sf::Font> mTextFont;
		sf::Text mText;

		sf::RectangleShape mBarFront;
		sf::RectangleShape mBarBack;

		sf::Color mForegroundColor;
		sf::Color mBackgroundColor;

		float mPercent;
	};
}