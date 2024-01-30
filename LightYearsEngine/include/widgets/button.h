#pragma once
#include "widgets/widget.h"
#include "framework/delegate.h"
#include <SFML/Graphics.hpp>

namespace ly
{
	class Button : public Widget
	{
	public:
		Button(const std::string& textString = "Button",
			const std::string& buttonTexturePath = "SpaceShooterRedux/PNG/UI/buttonBlue.png");

		virtual sf::FloatRect getBound() const;

		void setTextString(const std::string& newString);
		void setTextSize(unsigned int charSize);

		virtual bool handleEvent(const sf::Event& windowEvent) override;

		Delegate<> onButtonClicked;

	private:
		virtual void draw(sf::RenderWindow& windowRef) override;
		virtual void locationUpdated(const sf::Vector2f& location);
		virtual void rotationUpdated(float rotation);

		void centerText();

		shared<sf::Texture> mButtonTexture;
		sf::Sprite mButtonSprite;
		
		shared<sf::Font> mButtonFont;
		sf::Text mButtonText;

		sf::Color mButtonDefaultColor;
		sf::Color mButtonDownColor;
		sf::Color mButtonHoverColor;

		bool mIsButtonDown;
		void ButtonUp();
		void ButtonDown();
		void MouseHovered();
	};
}