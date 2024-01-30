#include "widgets/button.h"
#include "framework/AssetManager.h"

namespace ly
{
	Button::Button(const std::string& textString, const std::string& buttonTexturePath)
		:mButtonTexture{AssetManager::Get().LoadTexture(buttonTexturePath)},
		mButtonSprite{ *(mButtonTexture.get()) },
		mButtonFont{AssetManager::Get().LoadFont("SpaceShooterRedux/Bonus/kenvector_future.ttf")},
		mButtonText{textString, *(mButtonFont.get())},
		mButtonDefaultColor{128, 128, 128, 255},
		mButtonDownColor{64, 64, 64, 255},
		mButtonHoverColor{190, 190, 190, 255},
		mIsButtonDown{false}
	{
		mButtonSprite.setColor(mButtonDefaultColor);
		centerText();
	}
	sf::FloatRect Button::getBound() const
	{
		return mButtonSprite.getGlobalBounds();
	}
	void Button::setTextString(const std::string& newString)
	{
		mButtonText.setString(newString);
		centerText();
	}
	void Button::setTextSize(unsigned int charSize)
	{
		mButtonText.setCharacterSize(charSize);
		centerText();
	}
	bool Button::handleEvent(const sf::Event& windowEvent)
	{
		if (!getVisibility())
		{
			return false;
		}
		bool handled = false;
		if (windowEvent.type == sf::Event::MouseButtonReleased)
		{
			if (windowEvent.mouseButton.button == sf::Mouse::Left)
			{
				if (mButtonSprite.getGlobalBounds().contains(windowEvent.mouseButton.x, windowEvent.mouseButton.y) 
					&& mIsButtonDown)
				{
					onButtonClicked.broadCast();
					handled = true;
				}
			}

			ButtonUp();
		}
		else if (windowEvent.type == sf::Event::MouseButtonPressed)
		{
			if (mButtonSprite.getGlobalBounds().contains(windowEvent.mouseButton.x, windowEvent.mouseButton.y))
			{
				ButtonDown();
				handled = true;
			}
		}
		else if (windowEvent.type == sf::Event::MouseMoved)
		{
			if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (mButtonSprite.getGlobalBounds().contains(windowEvent.mouseMove.x, windowEvent.mouseMove.y))
				{
					MouseHovered();
				}
				else
				{
					ButtonUp();
				}
			}
		}

		return handled || Widget::handleEvent(windowEvent);
	}
	void Button::draw(sf::RenderWindow& windowRef)
	{
		windowRef.draw(mButtonSprite);
		windowRef.draw(mButtonText);
	}
	void Button::locationUpdated(const sf::Vector2f& location)
	{
		mButtonSprite.setPosition(location);
		centerText();
	}
	void Button::rotationUpdated(float rotation)
	{
		mButtonSprite.setRotation(rotation);
		mButtonText.setRotation(rotation);
	}

	void Button::centerText()
	{
		sf::Vector2f widgetCenter = getCenterPosition();
		sf::FloatRect textBound = mButtonText.getGlobalBounds();
		mButtonText.setPosition(widgetCenter - sf::Vector2f{ textBound.width / 2.f, textBound.height });
	}
	void Button::ButtonUp()
	{
		mIsButtonDown = false;
		mButtonSprite.setColor(mButtonDefaultColor);
	}
	void Button::ButtonDown()
	{
		mIsButtonDown = true;
		mButtonSprite.setColor(mButtonDownColor);
	}
	void Button::MouseHovered()
	{
		mButtonSprite.setColor(mButtonHoverColor);
	}
}