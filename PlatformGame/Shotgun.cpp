#include "Shotgun.h"
#include <iostream>

Shotgun::Shotgun(Node* parentNode, Bullets& bullets) : Weapon(parentNode, bullets)
{
	damage = 30.f;
	rateOfFire = 50.f;
	magazineSize = 7.f;
	ammo = magazineSize;
	bulletSpawnTimer = rateOfFire;
	reloadSpeed = 4.f;
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
	weaponSprite.setScale(sf::Vector2f(0.6f, 0.65f));
}


