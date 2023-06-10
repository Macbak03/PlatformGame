#include "Enemy.h"
#include <iostream>


Enemy::Enemy(Platform* platform, Node* parentNode) : platform(platform), Node(parentNode)
{
	enemyTexture = nullptr;
	enemySpeed = 0.f;
	enemyDamage = 0.f;
	enemyRateOfFire = 0.f;
	bulletSpawnTimer = 0.f;
	enemyHealth = 0;
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
	if (enemySpeed > 0)
	{
		enemyFacingLeft = false;
		enemyFacingRight = true;
	}
	if (enemySpeed < 0)
	{
		enemyFacingRight = false;
		enemyFacingLeft = true;
	}
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
	hit = true;
	if (hitColorTimer > 0)
	{
		enemySprite.setColor(sf::Color::Red);
	}

}

void Enemy::shoot(Node* parentNode)
{
	sf::Vector2f spawnPosition = getGlobalPosition();
	if (enemyFacingRight)
	{
		bullets.spawnBullet(enemyFacingLeft, sf::Vector2f(spawnPosition.x, spawnPosition.y + enemySize.y / 2 - 5.f), parentNode);
	}
	else if (enemyFacingLeft)
	{
		bullets.spawnBullet(enemyFacingLeft, sf::Vector2f(spawnPosition.x, spawnPosition.y + enemySize.y / 2 - 5.f), parentNode);
	}
	bulletSpawnTimer = 0.f;
}

void Enemy::updateShooting(float deltaTime, Node* parentNode)
{
	if (bullets.getBullets().size() < bullets.maxBullets)
	{
		if (bulletSpawnTimer >= enemyRateOfFire)
		{
			shoot(parentNode);

		}
		else
		{
			bulletSpawnTimer += deltaTime;
		}
	}
}

void Enemy::updateColorTimer(float deltaTime)
{
	hitColorTimer -= deltaTime;
	hit = false;
	if (hitColorTimer < 0)
	{
		enemySprite.setColor(enemyColor);
	}
}


void Enemy::updateEnemy(const sf::RenderTarget* target, float deltaTime, unsigned int weaponDamage, Node* parentNode, Node* playerNode, Collider playerCollider)
{
	moveEnemy();
	updateBounceCollision();
	updateEnemyAnimation(deltaTime);
	healthBar.updateHealthBarAnimation(weaponDamage, hit, getLocalPosition());
	updateColorTimer(deltaTime);
	updateShooting(deltaTime, parentNode);
	bullets.updateBullets(target, playerNode, playerCollider);
}

void Enemy::renderHealthBar(sf::RenderTarget* target)
{
	healthBar.drawHealthBar(target);
}


void Enemy::onDraw(sf::RenderTarget& target, const sf::Transform& transform) const
{
	target.draw(enemySprite, transform);
}
