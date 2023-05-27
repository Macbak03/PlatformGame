#include "Pistol.h"
#include <iostream>

Pistol::Pistol()
{
	damage = 10.f;
	rateOfFire = 50.f;
	magazineSize = 6.f;
	ammo = magazineSize;
	bulletSpawnTimer = rateOfFire;
	reloadSpeed = 4.f;
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
	weaponSprite.setOrigin(sf::Vector2f(0.f, weaponSprite.getGlobalBounds().top - 15.f));
}


