#include "widgets/TextWidget.h"
#include "framework/AssetManager.h"

namespace ly
{
	TextWidget::TextWidget(const std::string& textStr, const std::string& fontPath, unsigned int characterSize)
		:mFont{AssetManager::Get().LoadFont(fontPath)},
		mText{textStr, *(mFont.get()), characterSize}
	{

	}
	void TextWidget::setString(const std::string& newStr)
	{
		mText.setString(newStr);
	}
	void TextWidget::setTextSize(unsigned int newTextSize)
	{
		mText.setCharacterSize(newTextSize);
	}
	void TextWidget::locationUpdated(const sf::Vector2f& newLoc)
	{
		mText.setPosition(newLoc);
	}
	void TextWidget::rotationUpdated(float newRot)
	{
		mText.setRotation(newRot);
	}
	void TextWidget::draw(sf::RenderWindow& windowRef)
	{
		windowRef.draw(mText);
	}

	sf::FloatRect TextWidget::getBound() const
	{
		return mText.getGlobalBounds();
	}
}