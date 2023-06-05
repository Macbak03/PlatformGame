#include "Platform.h"
#include <iostream>

Platform::Platform(sf::Vector2f position, Node* parentNode) : Node(parentNode)
{
	platformSize = sf::Vector2f(125.f, 25.f);
	initTexture();
	initColider();
	setLocalPosition(position);
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
	platformSprite.setScale(sf::Vector2f(platformSize.x/platformTexture->getSize().x, platformSize.y / platformTexture->getSize().y));
}

void Platform::initColider()
{
	collider.size = platformSize;
}



sf::Sprite Platform::getShape()
{
	return platformSprite;
}


void Platform::onDraw(sf::RenderTarget& target, const sf::Transform& transform) const
{
	target.draw(platformSprite, transform);
}

const Collider& Platform::getCollider() const
{
	return this->collider;
}
