#include "Rifle.h"
#include <iostream>

Rifle::Rifle()
{
	damage = 5.f;
	rateOfFire = 15.f;
	magazineSize = 30.f;
	ammo = magazineSize;
	bulletSpawnTimer = rateOfFire;
	initTexture();
}

void Rifle::loadTexture()
{
	weaponTextureRight = new sf::Texture;
	if (!weaponTextureRight->loadFromFile("Textures/AK-47_right.png"))
	{
		std::cerr << "Could not load texture" << std::endl;
	}
	weaponTextureLeft = new sf::Texture;
	if (!weaponTextureLeft->loadFromFile("Textures/AK-47_left.png"))
	{
		std::cerr << "Could not load texture" << std::endl;
	}
}

void Rifle::initTexture()
{
	loadTexture();
	weaponSprite.setTexture(*weaponTextureRight);
	weaponSprite.setScale(sf::Vector2f(0.6f, 0.65f));
}


