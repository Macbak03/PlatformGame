#include "Marauder.h"
#include <iostream>

Marauder::Marauder(Platform* platform, Node* parentNode) : Enemy(platform, parentNode)
{
	enemySize = sf::Vector2f(100.f, 100.f);
	enemySpeed = 1.5f;
	enemyDamage = 10;
	animationSwitchTime = 0.2f;
	enemyMaxHealth = 200;
	enemyHealth = enemyMaxHealth;
	cashValue = 50;
	initTexture(sf::Vector2u(8, 2));
	initAnimation();
	initCollider();
}

void Marauder::loadTexture()
{
	enemyTexture = new sf::Texture;
	if (!enemyTexture->loadFromFile("Textures/Cowboy5.png"))
	{
		std::cerr << "Could not load texture" << std::endl;
	}
}


void Marauder::initTexture(sf::Vector2u imageCount)
{
	loadTexture();
	enemySprite.setTexture(*enemyTexture);
	enemySprite.setScale(sf::Vector2f((enemySize.x * imageCount.x) / enemyTexture->getSize().x, (enemySize.y * imageCount.y) / enemyTexture->getSize().y));
}

void Marauder::initCollider()
{
	collider.size.x = enemySize.x - 35.f;
	collider.size.y = enemySize.y - 35.f;
	collider.offset.x = -collider.size.x / 2;
	collider.offset.y = 25.f;
}

