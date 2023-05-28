#pragma once
#include<SFML/Graphics.hpp>
#include "Level.h"
#include "Animation.h"
class Enemy
{
private:
	void flip();
protected:
	sf::Texture* enemyTextrue;
	sf::Sprite enemySprite;
	Platform* platform;

	float enemySpeed;
	float enemyDamage;
	float enemyRateOfFire;
	float enemyHealth;

	virtual void loadTexture() = 0;
	virtual void initTexture() = 0;
	virtual void initAnimation() = 0;

public:
	Enemy(Platform* platform);
	~Enemy();
	virtual void updateEnemyAnimation(float& deltaTime) = 0;
	virtual sf::Vector2f getEnemyScale() = 0;
	void spawnEnemy(sf::Vector2f platformPosition);
	void moveEnemy();
	void updateBounceCollision();
	void updateEnemy(const sf::RenderTarget* target, float deltaTime);
	void renderEnemy(sf::RenderTarget* target);
};

