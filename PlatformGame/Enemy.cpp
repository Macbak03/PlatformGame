#include "Enemy.h"
#include <iostream>


Enemy::Enemy(Platform* platform) : platform(platform)
{
	enemyTextrue = nullptr;
	enemySpeed = 0.f;
	enemyDamage = 0.f;
	enemyRateOfFire = 0.f;
	enemyHealth = 0.f;
}

Enemy::~Enemy()
{
}

void Enemy::spawnEnemy(sf::Vector2f platformPosition)
{
	enemySprite.setPosition(platformPosition);
}

void Enemy::moveEnemy()
{
	enemySprite.move(sf::Vector2f(enemySpeed, 0));
}
void Enemy::flip()
{
	sf::Vector2f enemyScale = getEnemyScale();
	enemySpeed = -enemySpeed;
	enemySprite.setScale(sf::Vector2f(-enemyScale.x, enemyScale.y));
}

void Enemy::updateBounceCollision()
{
	
	enemySprite.setOrigin(sf::Vector2f(enemySprite.getLocalBounds().width / 2.f, 0));
	//collision with platform edges
	//left edge
	if (enemySprite.getGlobalBounds().left <= platform->getShape().getGlobalBounds().left - enemySprite.getOrigin().x)
	{
		flip();

	}
	//right edge
	else if (enemySprite.getGlobalBounds().left + enemySprite.getGlobalBounds().width  >= platform->getShape().getGlobalBounds().left 
		+ platform->getShape().getGlobalBounds().width + enemySprite.getOrigin().x)
	{
		flip();
	}
	/*if (enemySprite.getGlobalBounds().intersects(element.getShape().getGlobalBounds()))
	{
		enemySprite.setPosition(enemySprite.getGlobalBounds().left, element.getShape().getGlobalBounds().top - enemySprite.getGlobalBounds().height + 5.f);
	}*/
}

void Enemy::updateEnemy(const sf::RenderTarget* target, float deltaTime)
{
	moveEnemy();
	updateBounceCollision();
}

void Enemy::renderEnemy(sf::RenderTarget* target)
{
	target->draw(enemySprite);
}
