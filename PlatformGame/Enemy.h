#pragma once
#include<SFML/Graphics.hpp>
#include "Level.h"
#include "Animation.h"
class Enemy
{
protected:
	sf::Texture* enemyTextrue;
	sf::Sprite enemySprite;

	float enemySpeed;
	float enemyDamage;
	float enemyRateOfFire;
	float enemyHealth;

	virtual void loadTexture() = 0;
	virtual void initTexture() = 0;
	virtual void initAnimation() = 0;

public:
	Enemy();
	~Enemy();
	virtual void updateEnemyAnimation(float& deltaTime) = 0;
	virtual sf::Vector2f getEnemyScale() = 0;
	void spawnEnemy(sf::Vector2f platformPosition);
	void moveEnemy();
	void updateBounceCollision(const sf::RenderTarget* target, std::vector<Platform> platforms, const sf::Vector2f enemyScale);
	void updateEnemy(const sf::RenderTarget* target, float deltaTime, std::vector<Platform> platforms, const sf::Vector2f enemyScale);
	void renderEnemy(sf::RenderTarget* target);
};

