#include "Pistol.h"
#include <iostream>

Pistol::Pistol(Node* parentNode, Bullets& bullets) : Weapon(parentNode, bullets)
{
	weaponSize = sf::Vector2f(50.f, 25.f);
	damage = 10;
	rateOfFire = 1.f;
	magazineSize = 6;
	ammo = magazineSize;
	bulletSpawnTimer = rateOfFire;
	reloadTime = 4.f;
	initTexture();
}

void Pistol::loadTexture()
{
	weaponTexture = new sf::Texture;
	if (!weaponTexture->loadFromFile("Textures/revolver_right.png"))
	{
		std::cerr << "Could not load texture" << std::endl;
	}
}

void Pistol::initTexture()
{
	loadTexture();
	weaponSprite.setTexture(*weaponTexture);
	scale();
	weaponSprite.setOrigin(sf::Vector2f(0.f, weaponSprite.getGlobalBounds().top - 15.f));
}


