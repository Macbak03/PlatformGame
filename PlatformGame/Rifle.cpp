#include "Rifle.h"
#include <iostream>

Rifle::Rifle()
{
	this->damage = 5.f;
	this->rateOfFire = 10.f;
	this->ammoSize = 30.f;
	this->initTexture();
}

void Rifle::loadTexture()
{
	this->weaponTextureRight = new sf::Texture;
	if (!this->weaponTextureRight->loadFromFile("Textures/AK-47_right.png"))
	{
		std::cerr << "Could not load texture" << std::endl;
	}
	this->weaponTextureLeft = new sf::Texture;
	if (!this->weaponTextureLeft->loadFromFile("Textures/AK-47_left.png"))
	{
		std::cerr << "Could not load texture" << std::endl;
	}
}

void Rifle::initTexture()
{
	this->loadTexture();
	weaponSprite.setTexture(*weaponTextureRight);
	weaponSprite.setScale(sf::Vector2f(0.6f, 0.65f));
}


