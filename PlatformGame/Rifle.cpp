#include "Rifle.h"
#include <iostream>

Rifle::Rifle(Node* parentNode, Bullets& bullets) : Weapon(parentNode, bullets)
{
	damage = 10.f;
	rateOfFire = 15.f;
	magazineSize = 30.f;
	ammo = magazineSize;
	bulletSpawnTimer = rateOfFire;
	reloadSpeed = 3.f;
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
	weaponSprite.setScale(sf::Vector2f(0.6f, 0.65f));
}


