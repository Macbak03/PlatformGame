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
}

Enemy::~Enemy()
{
}


void Enemy::spawnEnemy()
{
	sf::Vector2f spawnPosition = sf::Vector2f(platform->getLocalPosition().x, platform->getLocalPosition().y - collider.size.y);
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

void Enemy::updateEnemy(const sf::RenderTarget* target, float deltaTime)
{
	moveEnemy();
	updateBounceCollision();
	updateEnemyAnimation(deltaTime);
}

void Enemy::drawCollider(sf::RenderTarget* target)
{
	sf::RectangleShape colliderShape;
	colliderShape.setSize(collider.size);
	colliderShape.setPosition(getGlobalPosition()+collider.offset);
	target->draw(colliderShape);
}


void Enemy::onDraw(sf::RenderTarget& target, const sf::Transform& transform) const
{
	target.draw(enemySprite, transform);
}
