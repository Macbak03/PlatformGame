#include "Bandit.h"
#include <iostream>

Bandit::Bandit(Platform* platform, Node* parentNode) : Enemy(platform, parentNode)
{
	enemySize = sf::Vector2f(85.f, 85.f);
	animationSwitchTime = 0.3f;
	enemySpeed = 1.f;
	enemyDamage = 5;
	enemyMaxHealth = 100;
	enemyHealth = enemyMaxHealth;
	cashValue = 10;
	initTexture(sf::Vector2u(8, 2));
	initAnimation();
	initCollider();
}

void Bandit::loadTexture()
{
	enemyTexture = new sf::Texture;
	if (!enemyTexture->loadFromFile("Textures/bandit1.png"))
	{
		std::cerr << "Could not load texture" << std::endl;
	}
}


void Bandit::initTexture(sf::Vector2u imageCount)
{
	loadTexture();
	enemySprite.setTexture(*enemyTexture);
	enemySprite.setScale(sf::Vector2f((enemySize.x *  imageCount.x) / enemyTexture->getSize().x , (enemySize.y * imageCount.y) / enemyTexture->getSize().y));
}

void Bandit::initCollider()
{
	collider.size.x = enemySize.x - 30.f;
	collider.size.y = enemySize.y - 20.f;
	collider.offset.x = -collider.size.x / 2;
	collider.offset.y = 10.f;
}



