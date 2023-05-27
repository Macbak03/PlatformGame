#include "Enemy.h"

Enemy::Enemy()
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

void Enemy::updateBounceCollision(const sf::RenderTarget* target, std::vector<Platform> platforms, sf::Vector2f enemyScale)
{
	enemySprite.setOrigin(sf::Vector2f(enemySprite.getLocalBounds().width / 2.f, 0));
	for (auto& element : platforms) 
	{
		if (enemySprite.getGlobalBounds().left <= element.getShape().getGlobalBounds().left)
		{
			enemySpeed = -enemySpeed;
		}
		if (enemySprite.getGlobalBounds().left + enemySprite.getGlobalBounds().width >= element.getShape().getGlobalBounds().left + element.getShape().getGlobalBounds().width)
		{
			enemySpeed = -enemySpeed;
		}
	}
	if (enemySpeed < 0)
	{
		enemySprite.setScale(sf::Vector2f(-enemyScale.x, enemyScale.y));
	}
	else
	{
		enemySprite.setScale(sf::Vector2f(enemyScale.x, enemyScale.y));
	}
}

void Enemy::updateEnemy(const sf::RenderTarget* target, float deltaTime, std::vector<Platform> platforms, sf::Vector2f enemyScale)
{
	moveEnemy();
	updateBounceCollision(target, platforms, enemyScale);
}

void Enemy::renderEnemy(sf::RenderTarget* target)
{
	target->draw(enemySprite);
}
