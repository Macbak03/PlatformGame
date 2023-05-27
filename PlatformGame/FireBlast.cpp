#include "FireBlast.h"
#include <iostream>

FireBlast::FireBlast(bool playerFacingRight, bool playerFacingLeft, sf::Vector2f weaponPosition)
{
	initTexture(playerFacingRight, playerFacingLeft);
	initPosition(weaponPosition);
}


void FireBlast::loadTexture()
{
	if (!fireBlastTexture->loadFromFile("Textures/weapon_fire.png"))
	{
		std::cerr << "Could not load texture" << std::endl;
	}
}

void FireBlast::initTexture(bool playerFacingRight, bool playerFacingLeft)
{
	loadTexture();
	fireBlastSprite.setTexture(*fireBlastTexture);
	if (playerFacingRight)
	{
		fireBlastSprite.setScale(sf::Vector2f(1.f, 1.f));
	}
	else if (playerFacingLeft)
	{
		fireBlastSprite.setScale(sf::Vector2f(-1.f, 1.f));
	}
}


void FireBlast::initPosition(sf::Vector2f weaponPosition)
{
	float x = weaponPosition.x;
	float y = weaponPosition.y + 10.f;
	fireBlastSprite.setPosition(sf::Vector2f(x,y));
}

void FireBlast::updateFireBlast(const sf::RenderTarget* target, bool playerFacingRight, bool playerFacingLeft)
{
	
}

void FireBlast::rednerFireBlast(sf::RenderTarget* target)
{
	target->draw(fireBlastSprite);
}
