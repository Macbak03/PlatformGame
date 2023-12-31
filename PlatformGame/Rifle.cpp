#include "Rifle.h"
#include <iostream>

Rifle::Rifle(Node* parentNode, Bullets& bullets) : Weapon(parentNode, bullets)
{
	weaponSize = sf::Vector2f(60.f, 32.5f);
	damage = 5;
	rateOfFire = 0.2f;
	magazineSize = 30;
	ammo = magazineSize;
	bulletSpawnTimer = rateOfFire;
	reloadTime = 3.f;
	initTexture();
}

void Rifle::loadTexture()
{
	weaponTexture = new sf::Texture;
	if (!weaponTexture->loadFromFile("Textures/AK-47_right.png"))
	{
		std::cerr << "Could not load texture" << std::endl;
	}
}

void Rifle::initTexture()
{
	loadTexture();
	weaponSprite.setTexture(*weaponTexture);
	scale();
}


