#include "SniperRifle.h"
#include <iostream>

SniperRifle::SniperRifle(Node* parentNode, Bullets& bullets) : Weapon(parentNode, bullets)
{
	damage = 50.f;
	rateOfFire = 100.f;
	magazineSize = 10.f;
	ammo = magazineSize;
	bulletSpawnTimer = rateOfFire;
	reloadSpeed = 5.f;
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
	weaponSprite.setScale(sf::Vector2f(0.6f, 0.65f));
}

