#include "Shotgun.h"
#include <iostream>

Shotgun::Shotgun(Node* parentNode) : Weapon(parentNode)
{
	damage = 30.f;
	rateOfFire = 50.f;
	magazineSize = 7.f;
	ammo = magazineSize;
	bulletSpawnTimer = rateOfFire;
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


