#include "SniperRifle.h"
#include <iostream>

SniperRifle::SniperRifle()
{
	this->damage = 50.f;
	this->rateOfFire = 1.f;
	this->ammoSize = 10.f;
	this->initTexture();
}


void SniperRifle::loadTexture()
{
	this->weaponTextureRight = new sf::Texture;
	if (!this->weaponTextureRight->loadFromFile("Textures/sniper_rifle_right.png"))
	{
		std::cerr << "Could not load texture" << std::endl;
	}
	this->weaponTextureLeft = new sf::Texture;
	if (!this->weaponTextureLeft->loadFromFile("Textures/sniper_rifle_left.png"))
	{
		std::cerr << "Could not load texture" << std::endl;
	}
}

void SniperRifle::initTexture()
{
	this->loadTexture();
	weaponSprite.setTexture(*weaponTextureRight);
	weaponSprite.setScale(sf::Vector2f(0.6f, 0.65f));
}

