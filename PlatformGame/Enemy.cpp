#include "Enemy.h"
#include <iostream>


Enemy::Enemy(Platform* platform, Node* parentNode) : platform(platform), Node(parentNode)
{
	enemyTextrue = nullptr;
	enemySpeed = 0.f;
	enemyDamage = 0.f;
	enemyRateOfFire = 0.f;
	enemyHealth = 0.f;
	enemySize = sf::Vector2f(0.f, 0.f);
	hitColorTimer = 0.f;
	enemyColor = enemySprite.getColor();
}

Enemy::~Enemy()
{
}


void Enemy::spawnEnemy()
{
	sf::Vector2f spawnPosition = sf::Vector2f(platform->getLocalPosition().x, platform->getLocalPosition().y - collider.size.y - collider.offset.y);
	setLocalPosition(spawnPosition);
}

void Enemy::moveEnemy()
{
	move(enemySpeed, 0);
}
void Enemy::flip()
{
	flipX();
	enemySpeed = -enemySpeed;
}

void Enemy::updateBounceCollision()
{
	sf::Vector2f enemyGlobalPosition = getGlobalPosition();
	sf::Vector2f platformGlobalPosition = platform->getGlobalPosition();
	Collider platformCollider = platform->getCollider();
	float enemyLeft = enemyGlobalPosition.x + collider.offset.x;
	float enemyRight = enemyLeft + collider.size.x;
	//collision with platform edges
	//left edge
	if (enemyLeft <=platformGlobalPosition.x + collider.offset.x)
	{
		flip();
	}
	//right edge
	else if (enemyRight >= platformGlobalPosition.x + platformCollider.size.x - collider.offset.x)
	{
		flip();
	}
	//std::cout << enemyLeft << std::endl;
}


void Enemy::drawCollider(sf::RenderTarget* target)
{
	sf::RectangleShape colliderShape;
	colliderShape.setSize(collider.size);
	colliderShape.setPosition(getGlobalPosition()+collider.offset);
	target->draw(colliderShape);
}

Collider& Enemy::getCollider()
{
	return collider;
}

void Enemy::setColorTimer(float value)
{
	hitColorTimer = value;
}

void Enemy::changeColor()
{
	if (hitColorTimer > 0)
	{
		enemySprite.setColor(sf::Color::Red);
	}
}

sf::Sprite& Enemy::getSprite()
{
	return enemySprite;
}

void Enemy::updateColorTimer(float deltaTime)
{
	hitColorTimer -= deltaTime;
	if (hitColorTimer < 0)
	{
		enemySprite.setColor(enemyColor);
	}
}



void Enemy::updateEnemy(const sf::RenderTarget* target, float deltaTime)
{
	moveEnemy();
	updateBounceCollision();
	updateEnemyAnimation(deltaTime);
	updateColorTimer(deltaTime);

}

void Enemy::onDraw(sf::RenderTarget& target, const sf::Transform& transform) const
{
	target.draw(enemySprite, transform);
}
