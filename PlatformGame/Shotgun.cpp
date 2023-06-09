#include "Shotgun.h"
#include <iostream>

Shotgun::Shotgun(Node* parentNode, Bullets& bullets) : Weapon(parentNode, bullets)
{
	weaponSize = sf::Vector2f(60.f, 32.5f);
	damage = 30;
	rateOfFire = 1.2f;
	magazineSize = 7;
	ammo = magazineSize;
	bulletSpawnTimer = rateOfFire;
	reloadTime = 4.f;
	initTexture();
}

void Shotgun::loadTexture()
{
	weaponTexture = new sf::Texture;
	if (!weaponTexture->loadFromFile("Textures/shotgun_right.png"))
	{
		std::cerr << "Could not load texture" << std::endl;
	}
}

void Shotgun::initTexture()
{
	loadTexture();
	weaponSprite.setTexture(*weaponTexture);
	scale();
}


