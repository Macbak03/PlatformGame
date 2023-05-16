#include "Pistol.h"
#include <iostream>

Pistol::Pistol()
{
	damage = 10.f;
	rateOfFire = 50.f;
	ammoSize = 6.f;
	bulletSpawnTimer = rateOfFire;
	initTexture();
}

void Pistol::loadTexture()
{
	weaponTextureRight = new sf::Texture;
	if (!weaponTextureRight->loadFromFile("Textures/revolver_right.png"))
	{
		std::cerr << "Could not load texture" << std::endl;
	}
	weaponTextureLeft = new sf::Texture;
	if (!weaponTextureLeft->loadFromFile("Textures/revolver_left.png"))
	{
		std::cerr << "Could not load texture" << std::endl;
	}
}

void Pistol::initTexture()
{
	loadTexture();
	weaponSprite.setTexture(*weaponTextureRight);
	weaponSprite.setScale(sf::Vector2f(0.5f, 0.45f));
}


