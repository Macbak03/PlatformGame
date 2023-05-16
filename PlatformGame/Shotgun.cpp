#include "Shotgun.h"
#include <iostream>

Shotgun::Shotgun()
{
	damage = 30.f;
	rateOfFire = 3.f;
	ammoSize = 7.f;
	initTexture();
}

void Shotgun::loadTexture()
{
	weaponTextureRight = new sf::Texture;
	if (!weaponTextureRight->loadFromFile("Textures/shotgun_right.png"))
	{
		std::cerr << "Could not load texture" << std::endl;
	}
	weaponTextureLeft = new sf::Texture;
	if (!weaponTextureLeft->loadFromFile("Textures/shotgun_left.png"))
	{
		std::cerr << "Could not load texture" << std::endl;
	}
}

void Shotgun::initTexture()
{
	loadTexture();
	weaponSprite.setTexture(*weaponTextureRight);
	weaponSprite.setScale(sf::Vector2f(0.6f, 0.65f));
}


