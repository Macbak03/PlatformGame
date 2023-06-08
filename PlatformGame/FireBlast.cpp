#include "FireBlast.h"
#include <iostream>

FireBlast::FireBlast(Node* parentNode) : Node(parentNode)
{
	fireBlastSize = sf::Vector2f(30.f, 30.f);
	drawTimer = 0.f;
	initTexture();
}


void FireBlast::loadTexture()
{
	fireBlastTexture = new sf::Texture;
	if (!fireBlastTexture->loadFromFile("Textures/weapon_fire.png"))
	{
		std::cerr << "Could not load texture" << std::endl;
	}
}


void FireBlast::initTexture()
{
	loadTexture();
	fireBlastSprite.setTexture(*fireBlastTexture);
	fireBlastSprite.setScale(sf::Vector2f(fireBlastSize.x / fireBlastTexture->getSize().x, fireBlastSize.y / fireBlastTexture->getSize().y));
}


void FireBlast::initPosition(sf::Vector2f weaponPosition)
{
	setLocalPosition(weaponPosition);
}

void FireBlast::setDrawTimer(float value)
{
	drawTimer = value;
}

void FireBlast::updateDrawTimer(float deltaTime)
{
	drawTimer -= deltaTime;
}



void FireBlast::onDraw(sf::RenderTarget& target, const sf::Transform& transform) const
{
	if (drawTimer > 0)
	{
		target.draw(fireBlastSprite, transform);
	}
}