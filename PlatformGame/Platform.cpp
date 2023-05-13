#include "Platform.h"
#include <iostream>

Platform::Platform(sf::Vector2f position)
{
	this->initTexture();
	this->setPosition(position);
}


void Platform::loadTexture()
{
	platformTexture = new sf::Texture;
	if (!this->platformTexture->loadFromFile("Textures/grass-2.png"))
	{
		std::cerr << "Could not load texture" << std::endl;
	}
}

void Platform::initTexture()
{
	this->loadTexture();
	this->platformSprite.setTexture(*platformTexture);
	this->platformSprite.setScale(sf::Vector2f(0.1f, 0.1f));
}


void Platform::setPosition(sf::Vector2f position)
{
	this->platformSprite.setPosition(position);
}

sf::Sprite Platform::getShape()
{
	return platformSprite;
}


void Platform::renderPlatform(sf::RenderTarget* target)
{
	target->draw(platformSprite);
}

