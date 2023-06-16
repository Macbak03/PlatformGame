#include "Thug.h"
#include <iostream>

Thug::Thug(Platform* platform, Node* parentNode) : Enemy(platform, parentNode)
{
	enemySize = sf::Vector2f(85.f, 85.f);
	enemySpeed = 2.f;
	enemyDamage = 20;
	animationSwitchTime = 0.2f;
	enemyMaxHealth = 500;
	enemyHealth = enemyMaxHealth;
	cashValue = 1000;
	initTexture(sf::Vector2u(8, 2));
	initAnimation();
	initCollider();
}

void Thug::loadTexture()
{
	enemyTexture = new sf::Texture;
	if (!enemyTexture->loadFromFile("Textures/thug.png"))
	{
		std::cerr << "Could not load texture" << std::endl;
	}
}


void Thug::initTexture(sf::Vector2u imageCount)
{
	loadTexture();
	enemySprite.setTexture(*enemyTexture);
	enemySprite.setScale(sf::Vector2f((enemySize.x * imageCount.x) / enemyTexture->getSize().x, (enemySize.y * imageCount.y) / enemyTexture->getSize().y));
}

void Thug::initCollider()
{
	collider.size.x = enemySize.x - 30.f;
	collider.size.y = enemySize.y - 20.f;
	collider.offset.x = -collider.size.x / 2;
	collider.offset.y = 10.f;
}

