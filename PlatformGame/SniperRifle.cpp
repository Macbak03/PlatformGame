#include "SniperRifle.h"
#include <iostream>

SniperRifle::SniperRifle(Node* parentNode) : Weapon(parentNode)
{
	damage = 50.f;
	rateOfFire = 100.f;
	magazineSize = 10.f;
	ammo = magazineSize;
	bulletSpawnTimer = rateOfFire;
	initTexture();
}


void SniperRifle::loadTexture()
{
	weaponTextureRight = new sf::Texture;
	if (!weaponTextureRight->loadFromFile("Textures/sniper_rifle_right.png"))
	{
		std::cerr << "Could not load texture" << std::endl;
	}
}

void SniperRifle::initTexture()
{
	loadTexture();
	weaponSprite.setTexture(*weaponTextureRight);
	weaponSprite.setScale(sf::Vector2f(0.6f, 0.65f));
}

