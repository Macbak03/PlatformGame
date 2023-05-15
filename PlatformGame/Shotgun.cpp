#include "Shotgun.h"
#include <iostream>

Shotgun::Shotgun()
{
	this->damage = 30.f;
	this->rateOfFire = 3.f;
	this->ammoSize = 7.f;
	this->initTexture();
}

void Shotgun::loadTexture()
{
	this->weaponTextureRight = new sf::Texture;
	if (!this->weaponTextureRight->loadFromFile("Textures/shotgun_right.png"))
	{
		std::cerr << "Could not load texture" << std::endl;
	}
	this->weaponTextureLeft = new sf::Texture;
	if (!this->weaponTextureLeft->loadFromFile("Textures/shotgun_left.png"))
	{
		std::cerr << "Could not load texture" << std::endl;
	}
}

void Shotgun::initTexture()
{
	this->loadTexture();
	weaponSprite.setTexture(*weaponTextureRight);
	weaponSprite.setScale(sf::Vector2f(0.6f, 0.65f));
}


