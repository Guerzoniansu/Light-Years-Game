#include "widgets/guage.h"
#include "framework/AssetManager.h"

namespace ly
{
	HealthBar::HealthBar(const sf::Vector2f& size, float initialPercent, const sf::Color& foregroundColor, const sf::Color& backgroundColor)
		:mTextFont{AssetManager::Get().LoadFont("SpaceShooterRedux/Bonus/kenvector_future.ttf")},
		mText{ "", *(mTextFont.get()) },
		mBarFront{size},
		mBarBack{size},
		mPercent{initialPercent},
		mForegroundColor{foregroundColor},
		mBackgroundColor{backgroundColor}
	{
		mBarFront.setFillColor(mForegroundColor);
		mBarBack.setFillColor(mBackgroundColor);
		setTextSize(16);
	}
	void HealthBar::updateValue(float value, float maxValue)
	{
		if (maxValue == 0) return;
		mPercent = value / maxValue;
		std::string displayStr = std::to_string((int)value);
		mText.setString(displayStr);

		sf::Vector2f barSize = mBarBack.getSize();
		mBarFront.setSize({ barSize.x * mPercent, barSize.y });
		centerText();
	}

	void HealthBar::setTextSize(unsigned int newTextSize)
	{
		mText.setCharacterSize(newTextSize);
	}

	void HealthBar::draw(sf::RenderWindow& windowRef)
	{
		windowRef.draw(mBarBack);
		windowRef.draw(mBarFront);
		windowRef.draw(mText);
	}

	void HealthBar::centerText()
	{
		sf::Vector2f widgetCenter = getCenterPosition();
		sf::FloatRect textBound = mText.getGlobalBounds();
		mText.setPosition(widgetCenter - sf::Vector2f{textBound.width / 2.f, textBound.height});
	}

	void HealthBar::locationUpdated(const sf::Vector2f& newLoc)
	{
		//mText.setPosition(newLoc);
		mBarFront.setPosition(newLoc);
		mBarBack.setPosition(newLoc);
		centerText();
	}

	void HealthBar::rotationUpdated(float newRot)
	{
		mText.setRotation(newRot);
		mBarFront.setRotation(newRot);
		mBarBack.setRotation(newRot);
	}

	sf::FloatRect HealthBar::getBound() const
	{
		return mBarBack.getGlobalBounds();
	}

	void HealthBar::setForeGroundColor(const sf::Color& color)
	{
		mBarFront.setFillColor(color);
	}

	void HealthBar::setBackGroundColor(const sf::Color& color)
	{
		mBarBack.setFillColor(color);
	}
}