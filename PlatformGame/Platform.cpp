#include "Platform.h"
#include <iostream>

Platform::Platform(sf::Vector2f position)
{
	initTexture();
	setPosition(position);
}


void Platform::loadTexture()
{
	platformTexture = new sf::Texture;
	if (!platformTexture->loadFromFile("Textures/grass-2.png"))
	{
		std::cerr << "Could not load texture" << std::endl;
	}
}

void Platform::initTexture()
{
	loadTexture();
	platformSprite.setTexture(*platformTexture);
	platformSprite.setScale(sf::Vector2f(0.15f, 0.1f));
}


void Platform::setPosition(sf::Vector2f position)
{
	platformSprite.setPosition(position);
}

sf::Sprite Platform::getShape()
{
	return platformSprite;
}


void Platform::renderPlatform(sf::RenderTarget* target)
{
	target->draw(platformSprite);
}

