#include "Animation.h"
#include <iostream>

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	imageChangeValue = 0;
	totalTime = 0.0f;
	currentImage.x = 0;

	uvRec.width = texture->getSize().x / (imageCount.x);
	uvRec.height = texture->getSize().y / (imageCount.y);
}

Animation::~Animation()
{
}

int Animation::updateAnimation(int row, float deltaTime)
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
	uvRec.left = currentImage.x * uvRec.width;
	uvRec.top = currentImage.y * uvRec.height;
	return currentImage.x;
}


