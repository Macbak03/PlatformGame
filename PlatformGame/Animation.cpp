#include "Animation.h"
#include <iostream>

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
	this->imageCount = imageCount;
	this->switchTime = switchTime;
	totalTime = 0.0f;
	currentImage.x = 0;

	uvRec.width = texture->getSize().x / (imageCount.x);
	uvRec.height = texture->getSize().y / (imageCount.y);
}

Animation::~Animation()
{
}

void Animation::updateAnimation(int row, float deltaTime)
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
}

void Animation::updateHealthAnimation(unsigned int weaponDamage, bool hit)
{
	currentImage.y = 0;
	if (hit)
	{
		currentImage.x -=  (weaponDamage) / 10;
		if (currentImage.x <= 0)
		{
			currentImage.x = 0;
		}
	}
	uvRec.left = currentImage.x * uvRec.width;
	uvRec.top = currentImage.y * uvRec.height;
}

void Animation::setCurrentImageX(unsigned int value)
{
	currentImage.x = value;
}
