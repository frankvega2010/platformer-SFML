#include "SpriteAnimation.h"


SpriteAnimation::SpriteAnimation()
{

}

SpriteAnimation::SpriteAnimation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.x = 0;

	uvRect.width = texture->getSize().x / static_cast<int>(imageCount.x);
	uvRect.height = texture->getSize().y / static_cast<int>(imageCount.y);
}


SpriteAnimation::~SpriteAnimation()
{
}

void SpriteAnimation::Update(int row, float deltaTime)
{
	currentImage.y = row;
	totalTime += deltaTime;

	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage.x++;

		if (currentImage.x >= imageCount.x)
		{
			currentImage.x = 0;
		}
	}

	uvRect.left = currentImage.x * uvRect.width;
	uvRect.top = currentImage.y * uvRect.height;

}

void SpriteAnimation::SetAnimation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.x = 0;

	uvRect.width = texture->getSize().x / static_cast<int>(imageCount.x);
	uvRect.height = texture->getSize().y / static_cast<int>(imageCount.y);
}
