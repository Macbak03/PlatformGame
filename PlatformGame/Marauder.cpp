#include "Marauder.h"
#include <iostream>

Marauder::Marauder(Platform* platform, Node* parentNode) : Enemy(platform, parentNode)
{
	enemySize = sf::Vector2f(100.f, 100.f);
	enemySpeed = 1.5f;
	enemyDamage = 5.f;
	enemyRateOfFire = 5.f;
	enemyHealth = 100.f;
	initTexture(sf::Vector2u(8, 2));
	initAnimation();
	initCollider();
}

void Marauder::loadTexture()
{
	enemyTextrue = new sf::Texture;
	if (!enemyTextrue->loadFromFile("Textures/Cowboy5.png"))
	{
		std::cerr << "Could not load texture" << std::endl;
	}
}


void Marauder::initTexture(sf::Vector2u imageCount)
{
	loadTexture();
	enemySprite.setTexture(*enemyTextrue);
	enemySprite.setScale(sf::Vector2f((enemySize.x * imageCount.x) / enemyTextrue->getSize().x, (enemySize.y * imageCount.y) / enemyTextrue->getSize().y));
}

void Marauder::initCollider()
{
	collider.size.x = enemySize.x - 35.f;
	collider.size.y = enemySize.y - 35.f;
	collider.offset.x = -collider.size.x / 2;
	collider.offset.y = 25.f;
}

void Marauder::initAnimation()
{
	animation = new Animation(enemyTextrue, sf::Vector2u(8, 2), 0.2f);
}



void Marauder::updateEnemyAnimation(float& deltaTime)
{
	setOrigin(enemySize.x / 4.f, 0.f);
	enemySprite.setTextureRect(animation->uvRec);
	animation->updateAnimation(1, deltaTime);
}