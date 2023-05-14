#include "Pistol.h"
#include <iostream>

Pistol::Pistol()
{
	this->damage = 10.f;
	this->rateOfFire = 2.f;
	this->ammoSize = 6.f;
	this->initTexture();
}

void Pistol::loadTexture()
{
	this->weaponTextureRight = new sf::Texture;
	if (!this->weaponTextureRight->loadFromFile("Textures/revolver_right.png"))
	{
		std::cerr << "Could not load texture" << std::endl;
	}
	this->weaponTextureLeft = new sf::Texture;
	if (!this->weaponTextureLeft->loadFromFile("Textures/revolver_left.png"))
	{
		std::cerr << "Could not load texture" << std::endl;
	}
}

void Pistol::initTexture()
{
	this->loadTexture();
	weaponSprite.setTexture(*weaponTextureRight);
	weaponSprite.setScale(sf::Vector2f(0.4f, 0.6f));
}


