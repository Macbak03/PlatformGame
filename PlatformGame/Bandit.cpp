#include "Bandit.h"
#include <iostream>

Bandit::Bandit(Platform* platform, Node* parentNode) : Enemy(platform, parentNode)
{
	enemySize = sf::Vector2f(85.f, 85.f);
	enemySpeed = 1.f;
	enemyDamage = 5.f;
	enemyRateOfFire = 5.f;
	enemyHealth = 100.f;
	initTexture(sf::Vector2u(8, 2));
	initAnimation();
	initCollider();
}

void Bandit::loadTexture()
{
	enemyTextrue = new sf::Texture;
	if (!enemyTextrue->loadFromFile("Textures/bandit1.png"))
	{
		std::cerr << "Could not load texture" << std::endl;
	}
}


void Bandit::initTexture(sf::Vector2u imageCount)
{
	loadTexture();
	enemySprite.setTexture(*enemyTextrue);
	enemySprite.setScale(sf::Vector2f((enemySize.x *  imageCount.x) / enemyTextrue->getSize().x , (enemySize.y * imageCount.y) / enemyTextrue->getSize().y));
}

void Bandit::initCollider()
{
	collider.size.x = enemySize.x - 30.f;
	collider.size.y = enemySize.y - 20.f;
	collider.offset.x = -collider.size.x / 2;
	collider.offset.y = 10.f;
}

void Bandit::initAnimation()
{
	animation = new Animation(enemyTextrue, sf::Vector2u(8, 2), 0.3f);
}



void Bandit::updateEnemyAnimation(float& deltaTime)
{
	setOrigin(enemySize.x /4.f , 0.f);
	enemySprite.setTextureRect(animation->uvRec);
	animation->updateAnimation(1, deltaTime);
}

