#include "Bandit.h"
#include <iostream>

Bandit::Bandit(Platform* platform) : Enemy(platform)
{
	enemySpeed = 1.f;
	enemyDamage = 5.f;
	enemyRateOfFire = 5.f;
	enemyHealth = 100.f;
	initTexture();
	initAnimation();
}

void Bandit::loadTexture()
{
	enemyTextrue = new sf::Texture;
	if (!enemyTextrue->loadFromFile("Textures/bandit1.png"))
	{
		std::cerr << "Could not load texture" << std::endl;
	}
}


void Bandit::initTexture()
{
	loadTexture();
	enemySprite.setTexture(*enemyTextrue);
	enemySprite.setScale(sf::Vector2f(1.8f, 1.8f));
}


void Bandit::initAnimation()
{
	animation = new Animation(enemyTextrue, sf::Vector2u(8, 2), 0.3f);
}

sf::Vector2f Bandit::getEnemyScale()
{
	return enemySprite.getScale();
}


void Bandit::updateEnemyAnimation(float& deltaTime)
{
	enemySprite.setTextureRect(animation->uvRec);
	animation->updateAnimation(1, deltaTime);
}

