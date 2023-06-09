#include "SniperRifle.h"
#include <iostream>

SniperRifle::SniperRifle(Node* parentNode, Bullets& bullets) : Weapon(parentNode, bullets)
{
	weaponSize = sf::Vector2f(60.f, 32.5f);
	damage = 50;
	rateOfFire = 2.f;
	magazineSize = 10;
	ammo = magazineSize;
	bulletSpawnTimer = rateOfFire;
	reloadTime = 5.f;
	initTexture();
}


void SniperRifle::loadTexture()
{
	weaponTexture = new sf::Texture;
	if (!weaponTexture->loadFromFile("Textures/sniper_rifle_right.png"))
	{
		std::cerr << "Could not load texture" << std::endl;
	}
}

void SniperRifle::initTexture()
{
	loadTexture();
	weaponSprite.setTexture(*weaponTexture);
	scale();
}

