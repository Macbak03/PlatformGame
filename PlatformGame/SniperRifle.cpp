#include "SniperRifle.h"
#include <iostream>

SniperRifle::SniperRifle()
{
	damage = 50.f;
	rateOfFire = 1.f;
	ammoSize = 10.f;
	initTexture();
}


void SniperRifle::loadTexture()
{
	weaponTextureRight = new sf::Texture;
	if (!weaponTextureRight->loadFromFile("Textures/sniper_rifle_right.png"))
	{
		std::cerr << "Could not load texture" << std::endl;
	}
	weaponTextureLeft = new sf::Texture;
	if (!weaponTextureLeft->loadFromFile("Textures/sniper_rifle_left.png"))
	{
		std::cerr << "Could not load texture" << std::endl;
	}
}

void SniperRifle::initTexture()
{
	loadTexture();
	weaponSprite.setTexture(*weaponTextureRight);
	weaponSprite.setScale(sf::Vector2f(0.6f, 0.65f));
}

